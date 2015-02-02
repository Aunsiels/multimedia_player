JFLAGS = -g
JC = javac
SRC = MainWindow.java 
CLASS = $(SRC:.java=.class)

main : $(CLASS)

%.class : %.java
	$(JC) $(JFLAGS) $^

clean:
	-$(RM) *.class
