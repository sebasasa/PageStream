all: pagestream

pagestream: simulator/engine.cpp
	clang++ -std=c++11 -Iinclude -Isketch simulator/engine.cpp -o pagestream -Llib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,@executable_path/lib

clean:
	rm -f pagestream
