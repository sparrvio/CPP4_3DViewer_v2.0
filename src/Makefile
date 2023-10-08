CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic -g
COVFLAGS = -fprofile-arcs -ftest-coverage
TFLAGS = -lgcov -lgtest -lstdc++
LFLAFG = -lm
GTEST=-lgtest -lgtest_main -pthread
SOURCES = tests/affine_test.cc model/*.cc controller/*.cc

VAR = $(shell pkg-config --cflags --libs check)

.PHONY: all clean full_clean install uninstall run test install uninstall dist dvi leakscheck stylecheck

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
RUN_TARGET = run
else 
RUN_TARGET = runLIN
endif

all: clean download install $(RUN_TARGET)

install:
	cd ./view/3DViewer && cmake . && $(MAKE) all
#	cp -R ./view/3DViewer/3DViewer.app ~/Desktop

run:
	@sleep 1
	open ./view/3DViewer/3DViewer.app

runLIN:

	@sleep 1
	cd ./view/3DViewer && ./3DViewer		

test: clean
	@ g++ $(CFLAGS) $(COVFLAGS) ./tests/affine_test.cc  ./model/model.cc ./model/affine_rotate_adapter.cc ./model/affine_transformations_strategy.cc ./model/facade.cc ./model/save_settings.cc ./controller/controller.cc -o test $(GTEST)
	./test

gcov_report: test
	geninfo --ignore-errors mismatch . -b . -o ./coverage.info --no-external 
	genhtml coverage.info -o ./coverage
	open coverage/index.html
	@rm -rf *.gcno
	@rm -rf *.gcda

# gcov_report: test
# 	$(CC) $(SOURCES) $(COVFLAGS) $(TFLAGS) -o gcov_report
# 	./gcov_report
# 	lcov -t "test" -o test.info -c -d .
# 	genhtml -o report test.info
# 	open ./report/index.html
# 	rm -rf *.gcno
# 	rm -rf *.gcda


download:
	mkdir -p ~/Desktop/File_obj
	curl -L -o ~/Desktop/File_obj/cube.obj 'https://drive.google.com/uc?export=download&id=1I0F1sWyw0hofjhT3AjT1MDYAX5XtQBZI'
	curl -L -o ~/Desktop/File_obj/chakram.obj 'https://drive.google.com/uc?export=download&id=1mQQYz0RcpsQR1MHRuHVtlS-grhNo0ibc'
#	curl -L -o ~/Desktop/File_obj/skull.obj 'https://drive.google.com/uc?export=download&id=13oT6WlPAZywXBVjZPxXOLUcn-QriM9V0'
#	curl -L -o ~/Desktop/File_obj/dog.obj 'https://drive.google.com/uc?export=download&id=14FYOVu-7q7i_xMvKJky_X0tvDW9bCs9T'
#	curl -L -o ~/Desktop/File_obj/elephant.obj 'https://drive.google.com/uc?export=download&id=11h7OQYN9OOLeQY87O3syhEQrnbonGNFa'
#	curl -L -o ~/Desktop/File_obj/three.obj 'https://drive.google.com/uc?export=download&id=1V2JhP6JIVwHAE8KVMvr0wYc4L6oBuYzP'

dist:
	tar czf ../dist.tar *

generatedvi:
	curl -L -o $(CURDIR)/docs/doxygen 'https://drive.google.com/uc?export=download&id=1arycp6Hm-ORDZnD5xodBwSoyUyNSao6p'
	cd docs && chmod 777 doxygen
	cd docs && ./doxygen Doxyfile 

dvi: generatedvi
	open docs/html/index.html

leakscheck: test
	CK_FORK=no leaks --atExit -- ./test     

stylecheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.cc *.h model/*.cc model/*.h controller/*.cc controller/*.h view/*.cc view/*.h 
	cp ../materials/linters/.clang-format .clang-format 
	clang-format -style=Google -i tests/*.cc model/*.cc model/*.h controller/*.cc controller/*.h view/3DViewer/*.cc view/3DViewer/*.h
	clang-format -style=Google -n tests/*.cc model/*.cc model/*.h controller/*.cc controller/*.h view/3DViewer/*.cc view/3DViewer/*.h
	rm -rf .clang-format

uninstall: clean
	@rm -rf ./view/3DViewer/3DViewer.app
	@rm -rf ./view/3DViewer/CMakeCache.txt
	@rm -rf ./view/3DViewer/CMakeFiles/
	@rm -rf ./view/3DViewer/Makefile
	@rm -rf ./view/3DViewer/3DViewer_autogen/
	@rm -rf ./view/3DViewer/cmake_install.cmake
	@rm -rf ./view/3DViewer/CMakeLists.txt.user*
	@rm -rf ~/Desktop/3DViewer.app
	@rm -rf ./view/3DViewer/.cmake/
	@rm -rf ./view/3DViewer/.qtc_clangd/
	@rm -rf ./view/3DViewer/Testing/
	@rm -rf ./view/3DViewer/qtcsettings.cmake
	@rm -rf ~/Desktop/File_obj
	@rm -rf gcov_report
	@rm -rf ~/Desktop/File_obj
	@rm -rf ~/Desktop/docs
	@rm -rf ~/colorsettings.txt


clean:
	@rm -rf *.out
	@rm -rf *.dSYM
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf *.info
	@rm -rf *.a
	@rm -rf *.log
	@rm -rf test
	@rm -rf CPPLINT.cfg
	@rm -rf cpplint.py
	@rm -rf report.*
	@rm -rf *.css
	@rm -rf index.html
	@rm -rf *.gcov
	@rm -rf *.gch
	@rm -rf C8_3DViewer_v1.0-1.tar.gz
	@rm -rf ../build/CMakeCache.txt
	@rm -rf ./report
	@rm -rf .clang-format
	@rm -rf ../build/
	@rm -rf lcov_report
	@rm -rf ./docs/html/
	@rm -rf ./docs/doxygen
	@rm -rf coverage/
	@rm -rf ./tests/colorsettings.txt

full_clean: clean
	@rm -rf *.o	

TARGET=test
VGFLAGS=--trace-children=yes --track-fds=all  --leak-check=full --show-leak-kinds=all --track-origins=yes

docker_run:
	bash -c "sh run.sh"

vg: $(TARGET) 
	valgrind $(VGFLAGS) ./$<
