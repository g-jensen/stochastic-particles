SRC_DIR = src
SPEC_DIR = spec
LIB_DIR = lib
DEPS_LOG = log/deps.log

all: mean resets survival_rate gates wait_times

.PHONY: src
src: src/* headers/*
	g++ -c src/*

.PHONY: mean
mean: src
	g++ -o mean examples/mean.cpp *.o

.PHONY: resets
resets: src
	g++ -o resets examples/resets.cpp *.o

.PHONY: survival_rate
survival_rate: src
	g++ -o survival_rate examples/survival_rate.cpp *.o

.PHONY: gates
gates: src
	g++ -o gates examples/gates.cpp *.o

.PHONY: wait_times
wait_times: src
	g++ -o wait_times examples/wait_times.cpp *.o

clean:
	rm -f *.o

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