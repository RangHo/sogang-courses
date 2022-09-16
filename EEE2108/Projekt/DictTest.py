class Pokemon:
  def __init__(self, name, type, health, is_knocked_out, is_legendary, Attk, Def):
    self.name = name
    self.type = type
    self.is_knocked_out = is_knocked_out
    self.max_health = health
    self.health = self.max_health
    self.is_legendary = is_legendary
    self.Attk = Attk
    self.Def = Def
  
  def __repr__(self):
    return "== Pokemon Information ==\nName: {}\nType: {}\nMaximun health: {}\nCurrent health: {}\nAttack: {} \nDefense: {}".format(self.name, self.type, self.max_health, self.health, self.Attk, self.Def)
  
  def ATTCC(self, other):
      

    DamageChart = {
        'Normal' : {'Rock' : 0.5, 'Ghost' : 0, 'Steel' : 0.5},
        'Fighting' : {'Fighting' : 1.5, 'Poison' : 0.5, 'Flying' : 0.5, 'Bug' : 0.5, 'Rock' : 1.5, 'Ghost' : 0, 'Steel' : 1.5, 'Ice' : 1.5, 'Psychic' : 0.5, 'Dark' : 1.5, 'Fairy' : 0.5},
        'Poison' : {'Poison': 0.5, 'Ground' : 0.5, 'Rock' : 0.5, 'Ghost' : 0.5, 'Steel' : 0, 'Grass' : 1.5, 'Fairy' : 1.5},
        'Ground' : {'Poison' : 1.5, 'Flying' : 0, 'Bug' : 0.5, 'Rock' : 1.5, 'Steel' : 1.5, 'Fire' : 1.5, 'Electric' : 1.5, 'Grass' : 0.5},
        'Flying' : {'Fighting' : 1.5, 'Bug' : 1.5, 'Rock' : 0.5, 'Electric' : 0.5, 'Grass' : 1.5},
        'Bug' : {'Fighting' : 0.5, 'Poison' : 0.5, 'Flying' : 0.5, 'Ghost' : 0.5, 'Steel' : 0.5, 'Fire' : 0.5, 'Grass' : 1.5, 'Psychic' : 1.5, 'Dark' : 1.5, 'Fairy' : 0.5},
        'Rock' : {'Fighting' : 0.5, 'Ground' : 0.5, 'Flying' : 1.5, 'Bug' : 1.5, 'Steel' : 0.5, 'Fire' : 1.5, 'Ice' : 1.5},
        'Ghost' : {'Normal' : 0, 'Ghost' : 0.5, 'Psychic' : 1.5, 'Dark' : 0.5},
        'Steel' : {'Rock' : 1.5, 'Steel' : 0.5, 'Fire' : 0.5, 'Water' : 0.5, 'Electric' : 0.5, 'Ice' : 1.5, 'Fairy' : 1.5},
        'Fire' : {'Bug' : 1.5, 'Rock' : 0.5, 'Steel' : 1.5, 'Fire' : 0.5, 'Water' : 0.5, 'Grass' : 1.5, 'Ice' : 1.5, 'Dragon' : 0.5},
        'Water' : {'Ground' : 1.5, 'Rock' : 1.5, 'Fire' : 1.5, 'Water' : 0.5, 'Grass' : 0.5, 'Dragon' : 0.5},
        'Electric' : {'Ground' : 0, 'Flying' : 1.5, 'Water' : 1.5, 'Electric' : 0.5, 'Grass' : 0.5, 'Dragon' : 0.5},
        'Grass' : {'Poison' : 0.5, 'Ground' : 1.5, 'Flying' : 0.5, 'Bug' : 0.5, 'Rock' : 1.5, 'Steel' : 0.5, 'Fire' : 0.5, 'Water' : 1.5, 'Grass' : 0.5, 'Dragon' : 0.5},
        'Ice' : {'Ground': 1.5, 'Flying' : 1.5, 'Steel' : 0.5, 'Fire' : 0.5, 'Water' : 0.5, 'Grass' : 1.5, 'Ice' : 0.5, 'Dragon' : 1.5},
        'Psychic' : {'Fighting' : 1.5, 'Poison' : 1.5, 'Steel' : 0.5, 'Psychic' : 0.5, 'Dark' : 0},
        'Dragon' : {'Steel' : 0.5, 'Dragon' : 1.5, 'Fairy' : 0},
        'Dark' : {'Fighting' : 0.5, 'Ghost' : 1.5, 'Psychic' : 1.5, 'Dark' : 0.5, 'Fairy' : 0.5},
        'Fairy' : {'Fighting' : 1.5, 'Poison' : 0.5, 'Steel' : 0.5, 'Fire' : 0.5, 'Dragon' : 1.5, 'Dark' : 1.5}

                     }
    try:
        Modifier = DamageChart[self.type][other.type]

    except KeyError:
        Modifier = 1
    
    print(Modifier)
    return 0



A = Pokemon('A', 'Fighting', 100, False, False, 100,100)
B = Pokemon('B', 'Normal', 100, False, False, 100,100)
C = Pokemon('C', 'Flying', 100, False, False, 100,100)

A.ATTCC(B)
A.ATTCC(C)