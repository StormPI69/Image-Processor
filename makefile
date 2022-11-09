run: 
	g++ driver.cpp PGMimageProcessor.cpp ConnectedComponent.cpp -o driver
	
clean:
	rm driver 
	rm *.o
test:
	g++ ConnectedComponentTest.cpp ConnectedComponent.cpp PGMimageProcessor.cpp catch.hpp -o drive
	./drive -s 3 10000 -t 60 chess.pgm