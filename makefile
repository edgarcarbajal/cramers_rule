CXXFLAGS+=-std=c++11 -Wall -Wextra -Werror -pedantic -I.

all: cramers_rule

cramers_rule: cramers_rule.cc matrix.cc matrix.h
	g++ $(CXXFLAGS) -o cramers_rule $^


clean:
	rm -f cramers_rule *.o

# Some times another 'phony' target is provided to easily force a 'clean' and then
# a rebuild of 'all' the targets.
world: clean all
