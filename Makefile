CC = g++ 
CFLAGS = -std=c++17
LDLIBS = -lncursesw -lstdc++fs 

all: main

clean:
	rm -f *.o neomatrix

asciiart.o: asciiart.cpp asciiart.h
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

colorManager.o: colorManager.cpp colorManager.h
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

commandManager.o: commandManager.cpp commandManager.h
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

effects.o: effects.cpp effects.h
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

infoManager.o: infoManager.cpp infoManager.h
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

main.o: main.cpp
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

menuManager.o: menuManager.cpp menuManager.h
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

screenManager.o: screenManager.cpp screenManager.h
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

settingsFile.o: settingsFile.cpp settingsFile.h
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

settingsManager.o: settingsManager.cpp settingsManager.h
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

titleManager.o: titleManager.cpp titleManager.h
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -c $<

main: asciiart.o colorManager.o commandManager.o effects.o infoManager.o main.o menuManager.o screenManager.o settingsFile.o settingsManager.o titleManager.o
	@echo "# Generating $@ "
	$(CC) $(CFLAGS) -o neomatrix $^ $(LDLIBS)
