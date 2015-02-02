/*******************************************************************************
*
* \file multimedia.h
* \brief Describe what is a multimedia file
* \author Julien Romero
* \version 0.1
* \date  10/12/2014
*
*
*Copyright (c) 2014 JulienRomero
*
*Permission is hereby granted, free of charge, to any person obtaining
*a copy of this software and associated documentation files (the
*"Software"), to deal in the Software without restriction, including
*without limitation the rights to use, copy, modify, merge, publish,
*distribute, sublicense, and/or sell copies of the Software, and to
*permit persons to whom the Software is furnished to do so, subject to
*the following conditions:
*
*The above copyright notice and this permission notice shall be
*included in all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
*NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
*LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
*OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
*WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*******************************************************************************/

import javax.swing.*;
import java.awt.event.*;
import java.awt.BorderLayout;
import java.awt.FlowLayout;

/*!
*
* \class MainWindow
* \brief This is the main window of the program.
*
*/

public class MainWindow extends JFrame {

     private static final long serialVersionUID = 1L;

     //A text area
     private JTextArea text;
     //2 buttons to write in JTextArea and one to close the program
     private JButton btn1, btn2, btn3;
     //The panel which will contain the buttons.
     private JPanel panel;
     //A scroller for the text
     private JScrollPane textscroller;
     
     /*!
     * \brief Main function of the program.
     *
     * Just creates the window.
     */

     public static void main(String argv[]) {
         new MainWindow();
     }

     /*!
     *
     * \brief Constructor
     *
     * Creates the main window.
     */

     public MainWindow() {

         //Elements declarations
         btn1 = new JButton("Add 1");
         btn2 = new JButton("Add 2");
	 btn3 = new JButton("Close");
	 text = new JTextArea(10,100);
	 panel = new JPanel();
         textscroller = new JScrollPane(text);

         //Listener of the buttons
         btn1.addActionListener(new ActionListener(){
             public void actionPerformed(ActionEvent e){
                 text.append("Add 1\n");
	     }
	 });

         btn2.addActionListener(new ActionListener(){
             public void actionPerformed(ActionEvent e){
                 text.append("Add 2\n");
	     }
	 });

         btn3.addActionListener(new ActionListener(){
             public void actionPerformed(ActionEvent e){
	         System.exit(0);
	     }
	 });

	 //Add the objects to the frame
	 this.add(textscroller, BorderLayout.CENTER);
	 panel.add(btn1, FlowLayout.LEFT);
	 panel.add(btn2, FlowLayout.CENTER);
	 panel.add(btn3, FlowLayout.RIGHT);

	 this.add(panel, BorderLayout.SOUTH);

	 setDefaultCloseOperation(EXIT_ON_CLOSE);
	 pack();
	 setVisible(true);
     }
}
