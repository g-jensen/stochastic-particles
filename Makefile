SRC_DIR = src
SPEC_DIR = spec
LIB_DIR = lib
DEPS_LOG = log/deps.log
OUTDIR = build
OBJ_DIR = $(OUTDIR)/obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: mean survival_rate resets gates late_wait_time early_wait_time

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	g++ -c $< -o $@

.PHONY: mean
mean: $(OBJS) | $(OUTDIR)
	g++ -o $(OUTDIR)/mean examples/mean.cpp $(OBJS)

.PHONY: resets
resets: $(OBJS) | $(OUTDIR)
	g++ -o $(OUTDIR)/resets examples/resets.cpp $(OBJS)

.PHONY: survival_rate
survival_rate: $(OBJS) | $(OUTDIR)
	g++ -o $(OUTDIR)/survival_rate examples/survival_rate.cpp $(OBJS)

.PHONY: gates
gates: $(OBJS) | $(OUTDIR)
	g++ -o $(OUTDIR)/gates examples/gates.cpp $(OBJS)

.PHONY: late_wait_time
late_wait_time: $(OBJS) | $(OUTDIR)
	g++ -o $(OUTDIR)/late_wait_time examples/late_wait_time.cpp $(OBJS)

.PHONY: early_wait_time
early_wait_time: $(OBJS) | $(OUTDIR)
	g++ -o $(OUTDIR)/early_wait_time examples/early_wait_time.cpp $(OBJS)

.PHONY: latex
latex:
	./scripts/compile_paper.sh

clean:
	rm -rf $(OUTDIR)

$(DEPS_LOG):
	@mkdir -p log
	@echo "Build started at $$(date)\n" > $(DEPS_LOG)

.PHONY: deps
deps: $(SPEC_DIR)/lib/catch.hpp $(SPEC_DIR)/lib/bdd.hpp $(LIB_DIR)/immer

$(SPEC_DIR)/lib/catch.hpp: $(DEPS_LOG)
	@echo "Installing Catch2..."
	@mkdir -p $(SPEC_DIR)/lib
	@curl -sL https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp \
    		-o $@ >> $(DEPS_LOG) 2>&1

$(SPEC_DIR)/lib/bdd.hpp: $(DEPS_LOG)
	@echo "Installing c2_bdd..."
	@mkdir -p $(SPEC_DIR)/lib
	@curl -sL https://raw.githubusercontent.com/s-ajensen/c2_bdd/refs/heads/master/c2_bdd.hpp \
            -o $@ >> $(DEPS_LOG) 2>&1

$(LIB_DIR)/immer: $(DEPS_LOG)
	@echo "Installing immer..."
	@mkdir -p lib
	@rm -rf lib/immer-temp
	@cd lib && \
	git clone --depth 1 --branch v0.8.1 https://github.com/arximboldi/immer.git immer-temp \
    		>> ../$(DEPS_LOG) 2>&1 && \
	mv immer-temp/immer . && \
	rm -rf immer-temp