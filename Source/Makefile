OBJS = main.o XMLParse.o Map.o Game.o Trigger.o Container.o Creature.o Item.o Room.o Player.o
CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)

IPA1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o IPA1

main.o : main.cpp Game.h Map.h XMLParse.h
	$(CC) $(CFLAGS) main.cpp

XMLParse.o : XMLParse.cpp XMLParse.h rapidxml.hpp
	$(CC) $(CFLAGS) XMLParse.cpp

Map.o : Map.cpp Map.h Room.h Creature.h Container.h Item.h XMLParse.h
	$(CC) $(CFLAGS) Map.cpp

Game.o : Game.cpp Game.h Map.h Player.h Room.h Trigger.h
	$(CC) $(CFLAGS) Game.cpp

Trigger.o : Trigger.cpp Trigger.h XMLParse.h
	$(CC) $(CFLAGS) Trigger.cpp

Container.o : Container.cpp Container.h XMLParse.h Trigger.h
	$(CC) $(CFLAGS) Container.cpp

Creature.o : Creature.cpp Creature.h XMLParse.h Trigger.h Item.h
	$(CC) $(CFLAGS) Creature.cpp

Item.o : Item.cpp Item.h XMLParse.h
	$(CC) $(CFLAGS) Item.cpp

Room.o : Room.cpp Room.h Container.h Item.h Creature.h XMLParse.h
	$(CC) $(CFLAGS) Room.cpp

Player.o : Player.cpp Player.h
	$(CC) $(CFLAGS) Player.cpp

clean:
	\rm *.o *~ IPA1

test:
	./IPA1 samples/containersample.xml <samples/containersample.txt >output/containerout
	diff output/containerout samples/containersample.out
	./IPA1 samples/creaturesample.xml <samples/creaturesample.txt >output/creatureout
	diff output/creatureout samples/creaturesample.out
	./IPA1 samples/itemsample.xml <samples/itemsample.txt >output/itemout
	diff output/itemout samples/itemsample.out
	./IPA1 samples/roomsample.xml <samples/roomsample.txt >output/roomout
	diff output/roomout samples/roomsample.out
	./IPA1 samples/triggersample.xml <samples/triggersample.txt >output/triggerout
	diff output/triggerout samples/triggersample.out
