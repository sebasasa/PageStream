all: u8g2_sim

u8g2_sim: simulator/engine.cpp
	clang++ -std=c++11 -Iinclude -Isketch simulator/engine.cpp -o u8g2_sim -Llib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,@executable_path/lib

clean:
	rm -f u8g2_sim
