import datetime

class Person(object):
    def __init__(self, name):
        self._name = name
        try:
            last_blank = name.rindex('')
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

    def __lt__(self,other):
        if self._last_name == other._last_name:
            return self._name < other._last_name
    
    def __str__(self):
        return self._name

class Politician(Person):
    def __init__(self, name, party = None):
        self._name = name
        self._party = party
    
    def get_party(self):
        return self._party
    
    def might_agree(self, other):
        if self._party == None or other._party == None:
            return True

        if self._party == other._party:
            return True
        else:
            return False


Tom = Politician("Tom","Democrat")
Mike = Politician("Mike")
Andy = Politician("Andy", "Democrat")
Don = Politician("Don", "Republican")

print("Tom:",Tom.get_party())
print("Mike:",Mike.get_party())
print("Andy:",Andy.get_party())
print("Don:",Don.get_party())

print("Tom and Mike (Same Party):",Tom.might_agree(Mike))
print("Tom and Andy (Party and No Party)",Tom.might_agree(Andy))
print("Tom and Don (Different Parties)",Tom.might_agree(Don))

