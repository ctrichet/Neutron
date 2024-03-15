CFLAGS=-std=c++11 -I. -I./tests
CXX=g++ $(CFLAGS) -c
LD=g++ -o
TARGETS = neutron.out
SRC_FOLDER = ./src/main
#MM OBJ_FOLDER
OBJ_FOLDER = ./obj/main
ECHO = @echo
HELP = help
#MM .PHONY: $(HELP)
.PHONY: $(HELP) efface

help:
	$(ECHO) "Voici les cibles disponibles"
    #$(ECHO) "aaaaaaaa "
    #$(ECHO) "  all Construire tous les binaires"
    #$(ECHO) "  clean Nettoyer les fichiers générés"
    #$(ECHO) "  test Exécuter les tests"
    #$(ECHO) "  install Installer le programme"
    #$(ECHO) ""

all: $(TARGETS)

#MM neutron.out: /neutron.o $(SRC_FOLDER)/knot.o $(SRC_FOLDER)/state.o $(SRC_FOLDER)/simulationState.o
neutron.out: $(OBJ_FOLDER)/neutron.o $(OBJ_FOLDER)/state.o $(OBJ_FOLDER)/simulationState.o $(OBJ_FOLDER)/stateFriend.o $(OBJ_FOLDER)/knot.o
	$(LD) $@ $^

#MM neutron.o: $(SRC_FOLDER)/neutron.cpp $(SRC_FOLDER)/knot.h $(SRC_FOLDER)/state.h $(SRC_FOLDER)/simulationState.h
$(OBJ_FOLDER)/neutron.o: $(SRC_FOLDER)/neutron.cpp $(SRC_FOLDER)/knot.h $(SRC_FOLDER)/state.h $(SRC_FOLDER)/simulationState.h
	@#MM $(CXX) $<
	$(CXX) $< -o $@

#MM knot.o: $(SRC_FOLDER)/knot.cpp $(SRC_FOLDER)/knot.h $(SRC_FOLDER)/state.h $(SRC_FOLDER)/simulationState.h
$(OBJ_FOLDER)/knot.o: $(SRC_FOLDER)/knot.cpp $(SRC_FOLDER)/knot.h $(SRC_FOLDER)/state.h $(SRC_FOLDER)/simulationState.h
	$(CXX) $< -o $@

#MM state.o: $(SRC_FOLDER)/state.cpp  $(SRC_FOLDER)/state.h #$(SRC_FOLDER)/simulationState.h
$(OBJ_FOLDER)/state.o: $(SRC_FOLDER)/state.cpp  $(SRC_FOLDER)/state.h #$(SRC_FOLDER)/simulationState.h
	$(CXX) $< -o $@

#MM simulationState.o: $(SRC_FOLDER)/simulationState.cpp $(SRC_FOLDER)/simulationState.h $(SRC_FOLDER)/state.h
$(OBJ_FOLDER)/simulationState.o: $(SRC_FOLDER)/simulationState.cpp $(SRC_FOLDER)/simulationState.h $(SRC_FOLDER)/state.h
	$(CXX) $< -o $@

#MM stateFriend.o: $(SRC_FOLDER)/stateFriend.cpp  $(SRC_FOLDER)/state.h $(SRC_FOLDER)/state.cpp
$(OBJ_FOLDER)/stateFriend.o: $(SRC_FOLDER)/stateFriend.cpp  $(SRC_FOLDER)/state.h $(SRC_FOLDER)/state.cpp
	$(CXX) $< -o $@



# Tests unitaires
TEST_FOLDER = ./src/test
TARGET_TESTS = $(TEST_FOLDER)/unitTests.out
TESTS_LIST = $(TEST_FOLDER)/stateUnitTest.out $(TEST_FOLDER)/knotUnitTest.out $(TEST_FOLDER)/knotUnitTest.out $(TEST_FOLDER)/simulationStateUnitTest.out
TESTS_LIST_SRC := $(wildcard $(TEST_FOLDER)/*.cpp)
TESTS_LIST_OBJ := $(patsubst %.cpp, %.o, $(TESTS_LIST_SRC))
#$(info TESTS_LIST : $(TESTS_LIST))
#$(info TESTS_LIST_SRC : $(TESTS_LIST_SRC))
#$(info TESTS_LIST_OBJ : $(TESTS_LIST_OBJ))

tests: $(TARGET_TESTS)
	$(TARGET_TESTS) -l; \
	$(TARGET_TESTS)

simulationStateUnitTest: $(TEST_FOLDER)/simulationStateUnitTest.out
	$(TEST_FOLDER)/simulationStateUnitTest.out

stateUnitTest: $(TEST_FOLDER)/stateUnitTest.out
	$(TEST_FOLDER)/stateUnitTest.out

knotUnitTest: $(TEST_FOLDER)/knotUnitTest.out
	$(TEST_FOLDER)/knotUnitTest.out

$(TARGET_TESTS): $(TESTS_LIST_OBJ) $(SRC_FOLDER)/knot.o $(SRC_FOLDER)/state.o $(SRC_FOLDER)/simulationState.o $(SRC_FOLDER)/stateFriend.o
	$(LD) $@ $^

$(TEST_FOLDER)/stateUnitTest.out: $(TEST_FOLDER)/unitTests.o $(TEST_FOLDER)/stateUnitTest.o $(SRC_FOLDER)/state.o $(SRC_FOLDER)/stateFriend.o $(SRC_FOLDER)/stateFriend.o
	$(LD) $@ $^

$(TEST_FOLDER)/simulationStateUnitTest.out: $(TEST_FOLDER)/unitTests.o $(TEST_FOLDER)/simulationStateUnitTest.o $(SRC_FOLDER)/simulationState.o $(SRC_FOLDER)/state.o $(SRC_FOLDER)/stateFriend.o
	$(LD) $@ $^

$(TEST_FOLDER)/knotUnitTest.out: $(TEST_FOLDER)/unitTests.o $(TEST_FOLDER)/knotUnitTest.o $(SRC_FOLDER)/knot.o $(SRC_FOLDER)/state.o $(SRC_FOLDER)/simulationState.o $(SRC_FOLDER)/stateFriend.o
	$(LD) $@ $^

clean:
	rm -f $(TARGETS) $(TARGET_TESTS) $(TESTS_LIST) $(TESTS_LIST_OBJ) *.o *.*~

#MM Ajout de la cible efface
efface:
	rm -f $(TARGETS) $(OBJ_FOLDER)/*.o
