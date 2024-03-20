# Design Project using C
### Linked List
The input file will be in the form of:<br>
"**First_name Last_name score\n(new line)**  <br>
**First_name Last_name score\n(new line) ...**"<br>
Create your own input file and test by yourself. The TA will run your executable file with his own test set.

In the report , explain your algorithms. Your code should have appropriate comments.<br>
Write a program that takes input from an input file and write the result into an output file.<br>
The program should run in MS DOS and get the input file name via the arguments in the main function, i.e., use int main(int argc and char *argv[]).<br>
The following 4 procedure runs sequentially.<br>

**Problem 1.** <br>
Create a linked list where each node in the linked list contains first_name last_name
score and grade.<br>
You need to determine the grade using the following table.<br>

| Score | Grade |
| --- | --- |
| 90~100 | A+ |
| 80~89 | A0 |
| 70~79 | B+ |
| 60~69 | B0 |
| 50~59 | C+ |
| 40~49 | C0 |
| 30~39 | D+ |
| 20~29 | D0 |
| 0~19 | F |

Use struct and malloc to create a node. Display the list as follows: <br>

 **First_name Last_name score grade**<br>

Then, display the following message and prompt:<br>

**"If you go to Problem 2, press any key"**<br>

When a key is entered, write the displayed result into result1.txt, and proceed to Problem 2.<br><br>

**Problem 2.** <br>
Sort the linked list based on the student's last name.<br>
Choose your own sorting your own sorting algorithm.<br>
Then, display the following message and prompt.<br>

**"If you go to Problem 3, press any key"**<br>

When any key is entered, write the displayed result into result2.txt, and proceed to Problem 3<br><br>

**Problem 3.** <br>
Take the student name as an input from the keyboard:<br>

**"Enter the student name: Elon Musk"**<br>

Then, remove the student, display the list of students, and take the input again.<br><br>

If the student does not exist, the following error message should be displayed, and take the input should be displayed, and take the input again.<br>
**"Elon Musk is not found in the list. Please try again."**<br>
If the input is **Go Next**, save the current list into result3.txt, and proceed to Problem 4.<br><br>

**Problem 4.** <br>
Insert a new student with first_name last_name score.<br>

**"Enter the new students (First name Last name score): Tony Stark 100"**<br>

Then, insert the student in the sorted list and display the list, and save the result into result4.txt and terminate the program. and terminate the program.<br>
