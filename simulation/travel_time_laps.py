import csv
import math
import sys
from fractions import Fraction


import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import numpy as np


def parse_value(s):
    s = s.strip()
    if s == "inf":
        return math.inf
    return float(Fraction(s))


def load_csv(path):
    results = {}
    with open(path) as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            phase, on_ratio, optimal_tt, _optimal_laps = [parse_value(c) for c in row]
            results[(phase, on_ratio)] = optimal_tt
    return results


def build_grid(results):
    phases = sorted(set(k[0] for k in results))
    on_ratios = sorted(set(k[1] for k in results))

    grid = np.full((len(on_ratios), len(phases)), np.nan)
    for (phase, on_ratio), travel_time in results.items():
        xi = phases.index(phase)
        yi = on_ratios.index(on_ratio)
        grid[yi, xi] = travel_time

    return phases, on_ratios, grid


def max_denominator(values):
    denoms = []
    for v in values:
        if not math.isinf(v):
            denoms.append(Fraction(v).limit_denominator(1000).denominator)
    return max(denoms) if denoms else 1


def fraction_label(val, common_denom):
    f = Fraction(val).limit_denominator(1000)
    numerator = round(f * common_denom)
    if common_denom == 1:
        return str(numerator)
    return f"{numerator}/{common_denom}"


def nice_fractions():
    nice = [0, 1]
    for d in [10, 8, 6, 5, 4, 3]:
        for n in range(1, d):
            f = Fraction(n, d)
            if f not in nice:
                nice.append(f)
    return sorted(set(nice))


def select_nice_ticks(values, max_ticks):
    n = len(values)
    if n <= max_ticks:
        return list(range(n))

    nice = nice_fractions()

    for num_ticks in range(max_ticks, 2, -1):
        if n % num_ticks == 0:
            step = n // num_ticks
            indices = list(range(0, n, step))

            all_nice = True
            for idx in indices:
                f = Fraction(values[idx]).limit_denominator(1000)
                if f not in nice:
                    all_nice = False
                    break

            if all_nice:
                return indices

    for num_ticks in range(max_ticks, 2, -1):
        if n % num_ticks == 0:
            step = n // num_ticks
            return list(range(0, n, step))

    step = max(1, n // max_ticks)
    return list(range(0, n, step))


def render(path, phases, on_ratios, grid):
    granularity = len(phases)
    travel_times = [k / granularity for k in range(1, granularity)]
    n_colors = len(travel_times)
    tt_to_index = {tt: i for i, tt in enumerate(travel_times)}
    index_grid = np.full_like(grid, np.nan)
    for yi in range(grid.shape[0]):
        for xi in range(grid.shape[1]):
            if not np.isnan(grid[yi, xi]):
                index_grid[yi, xi] = tt_to_index[grid[yi, xi]]

    all_values = list(phases) + list(on_ratios) + list(travel_times)
    common_denom = max_denominator(all_values)

    n_phases = len(phases)
    n_on_ratios = len(on_ratios)

    fig_w = 12
    fig_h = 10
    cell_size = min((fig_w - 2.5) / n_phases, (fig_h - 2) / n_on_ratios)

    cmap = plt.cm.viridis.resampled(n_colors)
    norm = mcolors.BoundaryNorm(boundaries=np.arange(-0.5, n_colors), ncolors=n_colors)

    fig, ax = plt.subplots(figsize=(fig_w, fig_h))
    im = ax.pcolormesh(
        np.arange(n_phases + 1) - 0.5,
        np.arange(n_on_ratios + 1) - 0.5,
        index_grid,
        cmap=cmap,
        norm=norm,
    )

    max_axis_ticks = int(fig_w / 0.5)
    tick_indices = select_nice_ticks(phases, max_axis_ticks)

    ax.set_xticks(tick_indices)
    ax.set_xticklabels([fraction_label(phases[i], common_denom) for i in tick_indices])

    ax.set_yticks(tick_indices)
    ax.set_yticklabels([fraction_label(phases[i], common_denom) for i in tick_indices])

    ax.tick_params(labelsize=max(8, min(14, int(140 / max(n_phases, n_on_ratios)))))

    ax.set_xlabel("Phase")
    ax.set_ylabel("On Ratio")
    ax.set_title("Optimal Travel Time (most laps)")

    actual_values = sorted(set(v for v in grid.flat if not np.isnan(v)))
    actual_indices = [tt_to_index[val] for val in actual_values]

    max_cbar_ticks = int(fig_h / 0.4)
    selected = select_nice_ticks(
        [travel_times[i] for i in actual_indices], max_cbar_ticks
    )
    selected_indices = [actual_indices[i] for i in selected]

    selected_colors = [cmap(i / (n_colors - 1)) for i in selected_indices]
    compact_cmap = mcolors.ListedColormap(selected_colors)
    compact_norm = mcolors.BoundaryNorm(
        boundaries=np.arange(len(selected_indices) + 1), ncolors=len(selected_indices)
    )

    sm = plt.cm.ScalarMappable(cmap=compact_cmap, norm=compact_norm)
    cbar = fig.colorbar(sm, ax=ax, ticks=np.arange(len(selected_indices)) + 0.5)
    cbar.ax.set_yticklabels(
        [fraction_label(travel_times[i], common_denom) for i in selected_indices]
    )
    cbar.set_label("Travel Time")

    show_labels = cell_size >= 0.5
    if show_labels:
        fontsize = max(4, min(7, int(cell_size * 8)))
        for yi in range(n_on_ratios):
            for xi in range(n_phases):
                if not np.isnan(grid[yi, xi]):
                    label = fraction_label(grid[yi, xi], common_denom)
                    bg_val = index_grid[yi, xi] / (n_colors - 1) if n_colors > 1 else 0
                    text_color = "white" if bg_val < 0.5 else "black"
                    ax.text(
                        xi,
                        yi,
                        label,
                        ha="center",
                        va="center",
                        fontsize=fontsize,
                        color=text_color,
                    )

    fig.tight_layout()
    fig.savefig(path, dpi=150)
    print(f"Saved to {path}")


def main():
    csv_path = sys.argv[1] if len(sys.argv) > 1 else "output.csv"
    out_path = sys.argv[2] if len(sys.argv) > 2 else "visualization.png"

    results = load_csv(csv_path)
    phases, on_ratios, grid = build_grid(results)
    render(out_path, phases, on_ratios, grid)


if __name__ == "__main__":
    main()
