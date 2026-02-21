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
            phase, on_ratio, optimal_tt, _optimal_ls = [parse_value(c) for c in row]
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


def fraction_label(val, denom_limit):
    f = Fraction(val).limit_denominator(denom_limit)
    if f.denominator == 1:
        return str(f.numerator)
    return f"{f.numerator}/{f.denominator}"


def thin_ticks(n, max_ticks):
    if n <= max_ticks:
        return list(range(n))
    step = math.ceil(n / max_ticks)
    return list(range(0, n, step))


def render(path, phases, on_ratios, grid):
    travel_times = sorted(set(grid[~np.isnan(grid)].flat))
    n_colors = len(travel_times)
    tt_to_index = {tt: i for i, tt in enumerate(travel_times)}
    index_grid = np.full_like(grid, np.nan)
    for yi in range(grid.shape[0]):
        for xi in range(grid.shape[1]):
            if not np.isnan(grid[yi, xi]):
                index_grid[yi, xi] = tt_to_index[grid[yi, xi]]

    all_values = list(phases) + list(on_ratios) + list(travel_times)
    denom_limit = max_denominator(all_values) * 2

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
    x_tick_indices = thin_ticks(n_phases, max_axis_ticks)
    ax.set_xticks(x_tick_indices)
    ax.set_xticklabels([fraction_label(phases[i], denom_limit) for i in x_tick_indices])

    max_y_ticks = int(fig_h / 0.5)
    y_tick_indices = thin_ticks(n_on_ratios, max_y_ticks)
    ax.set_yticks(y_tick_indices)
    ax.set_yticklabels([fraction_label(on_ratios[i], denom_limit) for i in y_tick_indices])

    ax.tick_params(labelsize=max(8, min(14, int(140 / max(n_phases, n_on_ratios)))))

    ax.set_xlabel("Phase")
    ax.set_ylabel("On Ratio")
    ax.set_title("Optimal Travel Time (highest lifespan)")

    max_cbar_ticks = int(fig_h / 0.4)
    cbar_tick_indices = thin_ticks(n_colors, max_cbar_ticks)
    cbar = fig.colorbar(im, ax=ax, ticks=cbar_tick_indices)
    cbar.ax.set_yticklabels([fraction_label(travel_times[i], denom_limit) for i in cbar_tick_indices])
    cbar.set_label("Travel Time")

    show_labels = cell_size >= 0.5
    if show_labels:
        fontsize = max(4, min(7, int(cell_size * 8)))
        for yi in range(n_on_ratios):
            for xi in range(n_phases):
                if not np.isnan(grid[yi, xi]):
                    label = fraction_label(grid[yi, xi], denom_limit)
                    bg_val = index_grid[yi, xi] / (n_colors - 1) if n_colors > 1 else 0
                    text_color = "white" if bg_val < 0.5 else "black"
                    ax.text(xi, yi, label, ha="center", va="center",
                            fontsize=fontsize, color=text_color)

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
