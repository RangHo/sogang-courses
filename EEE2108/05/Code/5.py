import datetime

class Person(object):
    
    def __init__(self, name):
        self._name = name
        try:
            last_blank = name.rindex(' ')
            self._last_name = name[last_blank+1:]
        except:
            self._last_name = name
        self.birthday = None
        
    def get_name(self):
        return self._name
    
    def get_last_name(self):
        return self._last_name
    
    def set_birthday(self, birthdate):
        self._birthday = birthdate
        
    def get_age(self):
        if self._birthday == None:
            raise ValueError
        return (datetime.date.today() - self._birthday).days
    
    def __lt__(self, other):
        if self._last_name == other._last_name:
            return self._name < other._name
        return self._last_name < other._last_name
    
    def __str__(self):
        return self._name

class MIT_person(Person):
    
    _next_id_num = 0 
    
    def __init__(self, name):
        super().__init__(name)
        self._id_num = MIT_person._next_id_num
        MIT_person._next_id_num += 1
        
    def get_id_num(self):
        return self._id_num
    
    def __lt__(self, other):
        return self._id_num < other._id_num

class Student(MIT_person):
    pass

def is_student(self):
    return isinstance(self, Student)

#----------------- //위의 코드는 Grades를 제대로 동작시키기 위해 필요한 책의 이전 코드     

# # Figure 10-6 from page 198
class Grades(object):

    def __init__(self):
        self._students = []
        self._grades = {}
        self._is_sorted = True

    def add_student(self, student):
        if student in self._students:
            raise ValueError('Duplicate student')
        self._students.append(student)
        self._grades[student.get_id_num()] = []
        self._is_sorted = False

    def add_grade(self, student, grade):
        try:
            self._grades[student.get_id_num()].append(grade)
        except:
            raise ValueError('Student not in mapping')

    def get_grades(self, student):
        try:
            return self._grades[student.get_id_num()][:]
        except:
            raise ValueError('Student not in mapping')

    def get_students(self):
        if not self._is_sorted:
            self._students.sort()
            self._is_sorted = True
        return self._students[:]
        
#------------------// 여기서부터 과제 5
  
    def get_students_above(self,grade):
        _Output = []
        for i in range(len(self.get_students())):
           #print(i)
           if (sum(self.get_grades(self.get_students()[i]))/len(self.get_grades(self.get_students()[i]))) > grade:
               _Output.append(self.get_students()[i])
        return _Output

#------------------// 아래는 테스트용 정의 및 프린트
course = Grades()

S1= Student('Bernie')
S2= Student('Chad')
S3= Student('Cheems')
S4= Student('Pop_Cat')
S5= Student('Sander')


course.add_student(S1)
course.add_student(S2)
course.add_student(S3)
course.add_student(S4)
course.add_student(S5)

course.add_grade(S1,100)
course.add_grade(S2,90)
course.add_grade(S3,80)
course.add_grade(S4,70)
course.add_grade(S5,60)

course.add_grade(S1,100)
course.add_grade(S2,90)
course.add_grade(S3,80)
course.add_grade(S4,70)
course.add_grade(S5,0)

course.add_grade(S1,100)
course.add_grade(S2,90)
course.add_grade(S3,80)
course.add_grade(S4,70)
course.add_grade(S5,0)

print(*course.get_students_above(60))
