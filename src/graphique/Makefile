JFLAGS = -g
JC = javac
SRC = MainWindow.java Client.java
CLASS = $(SRC:.java=.class)

main : $(CLASS)

%.class : %.java
	$(JC) $(JFLAGS) $^

clean:
	-$(RM) *.class
