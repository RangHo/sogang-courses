class Int_set(object):
    def __init__(self):
        self._vals = []
    
    def insert(self,e):
        if e not in self._vals:
            self._vals.append(e)
    
    def member(self,e):
        return e in self._vals
    
    def remove(self,e):
        try:
            self._vals.remove(e)
        except:
            raise ValueError(str(e) + 'Not Found')
    
    def get_members(self):
        return self._vals[:]

    def __str__(self):
        if self._vals == []:
            return '{}'
        self._vals.sort()
        result = ''
        for e in self._vals:
            result = result + str(e) + ','
        return f'{{{result[:-1]}}}'
#--------------------------------------    
    def __add__(self,other):
        new_val = Int_set()
        new_val._vals = self._vals + other._vals
        return new_val
#--------------------------------------   


s = Int_set()
s.insert(3)
s.insert(6)
s.insert(9)
s.insert(123456)

t = Int_set()
t.insert(69)
t.insert(177013)

print("Before add: s =",s)

s = s + t

print("After add:: s =",s)