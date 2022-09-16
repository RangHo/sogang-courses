#20201510 이찬혁, (학번 입력 바람) 박준영 Python Term Project
#Pokemon Class 및 Method, Trainer Class 및 Method: 이찬혁
# CSV 입력처리, Dataframe 설정 및 Pokemon Assignment: 박준영 

class Pokemon: # 포켓몬 틀라스
  def __init__(self, name, type1, type2, health, Attk, Def, is_legendary):
    self.name = name
    self.type1 = type1
    self.type2 = type2
    self.is_knocked_out = False
    self.max_health = health
    self.health = health
    self.is_legendary = is_legendary
    self.Attk = Attk
    self.Def = Def
  
  def __repr__(self):
    if self.is_legendary == True:
      return "\n== Pokemon Information ==\n\n**Congratulations! Your pokemon is a legendary pokemon!**\nName: {}\nType 1: {}\nType 2: {} \nMaximun health: {}\nCurrent health: {}\nAttack: {} \nDefense: {}\n".format(self.name, self.type1, self.type2, self.max_health, self.health, self.Attk, self.Def)
    else:
      return "\n== Pokemon Information ==\n\nName: {}\nType 1: {}\nType 2: {}\nMaximun health: {}\nCurrent health: {}\nAttack: {} \nDefense: {}\n".format(self.name, self.type1, self.type2, self.max_health, self.health, self.Attk, self.Def)
  

#-----부활. 부활 가능시 체력을 1로 부활, 이미 살아있다면 살아있다고 띄움.-----#
  def revive(self): 
    if self.is_knocked_out:
      self.is_knocked_out = False
      self.health = 1
      print("{} has been revived with {} health!".format(self.name, self.health))
    else:
      print("{} is not knocked out.".format(self.name))


#-----기절. 기절 가능시 기절상태로 만듬. 이미 기절해있다면 기절해있다고 띄움.-----#
  def knock_out(self): 
    if self.health != 0: # lose_health 에서 이미 체력을 0으로 설정하기는 하나, 만약 이 함수가 따로 호출될 경우를 위해 또 0으로 설정.
      self.health = 0
    if self.is_knocked_out:
      print("{} is already knocked out.".format(self.name))
    else:
      self.is_knocked_out = True
      print("{} is knocked out!".format(self.name))


#-----#데미지. dmg의 값만큼 데미지를 입음.-----#
  def lose_health(self, dmg): 
    self.health -= dmg
    if self.health <= 0: #데미지를 너무 많이 입에 체력이 0 이하로 떨어지면, 체력을 0으로 설정한 뒤, 기절상태로 만듦.
      self.health = 0  
      self.knock_out()


#-----회복. heal 만큼의 체력을 회복함. 과치료 상태가 도지 않게 최대체력에서 힐을 끊음.-----#
  def gain_health(self, heal):   
    if self.is_knocked_out == False: 
      self.health += heal
      if self.health >= self.max_health:
        self.health = self.max_health
        print("{} healed to max health!".format(self.name))
      else:
        print("{} gained {} health!".format(self.name, heal))
      print("Current health: {}".format(self.health))
    else:
      print("Pokemon fainted; Cannot heal!")  #이미 기절해있으면 체력 회복을 못함.


#------공격. self의 포켓몬이 other의 포켓몬을 공격함.-----#
  def attack(self, other):
    attack = self.Attk
    defense = other.Def
    Modifier = 1

    if self.is_knocked_out == True: # 기절 시 공격 못함
      print("{} is knocked out!".format(self.name))
      return
    
    DamageChart = { #데미지 상성표.
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
        Modifier = DamageChart[self.type1][other.type1] #데미지 상성표에 따라 Modifier를 설정. 효과가 굉장하다: 1.5배, 효과가 별로: 0.5배
    except KeyError:
        Modifier = 1 #데미지 상성표에 표시가 되지 않았을 경우, Modifier를 1로 설정.

    try:
        Modifier = DamageChart[self.type1][other.type2]
    except KeyError:
        Modifier = Modifier 

    try:
        Modifier = DamageChart[self.type2][other.type1] 
    except KeyError:
        Modifier = Modifier

    try:
        Modifier = DamageChart[self.type2][other.type2] 
    except KeyError:
        Modifier = Modifier

    dmg = Modifier * (attack - defense)
    dmg = abs(dmg)

    # dmg의 값을 바탕으로 실제로 공격을 함
    print("{} attacked {}!".format(self.name, other.name))

    if Modifier == 1.5:
      print("It was very effective!") # 효과가 굉장했다!
    elif Modifier == 0.5:
      print("It was not very effective...") # 효과가 별로인듯 하다...
    elif Modifier == 0:
      print("There was no effect!") #효과읎음
    
    print("{} dealt {} damage to {}.".format(self.name, dmg, other.name))
    other.lose_health(dmg)
    print("Enemy Health: {}".format(other.health))
    print("")

  def get_knocked_out(self): # 기절인지 아닌지를 return
    return self.is_knocked_out

  def get_health(self): # 현재 체력을 return
    return self.health






#==========] Trainer Class [==========#

class Trainer: #트레이너 클라스
  def __init__(self, name, pokemon_list, potions, current_pokemon):
    self.name = name
    self.pokemon_list = pokemon_list
    self.potions = potions
    self.current_pokemon = current_pokemon
    self.Lost = False
  
  def __repr__(self):
    namelist = []
    i = 0
    while i < len(self.pokemon_list):
      namelist.append(self.pokemon_list[i].name)
      i += 1

    return "== Trainer information ==\nName:{} \nPokemons: {}\nPotions: {} \nCurrent pokemon: {} \n{}".format(self.name, namelist, self.potions, self.current_pokemon.name, self.current_pokemon)
  

#-----포션 사용. 포션이 있으면 포션을 사용해서 체력 100을 회복.-----#
  def use_potion(self):
    if self.potions > 0:
      print("{} used a potion!".format(self.name))
      if self.current_pokemon.is_knocked_out == True:
        print("Potion was not used.")
      elif self.current_pokemon.health < self.current_pokemon.max_health:
        self.current_pokemon.gain_health(100)
        self.potions -= 1
        
        print("{} has {} potions left.\n".format(self.name, self.potions))
      else:
        print("Pokemon already has maximum health.\n")
    else:
      print("No potions available!\n")
  

#-----공격. Self의 현 포켓몬이 Other의 현 포켓몬을 공격함.-----#
  def attack(self, other):
    self.current_pokemon.attack(other.current_pokemon)

#-----다음 포켓몬으로 변경. 변경 가능한 다음 포켓몬으로 현 포켓몬을 설정. 모든 포켓몬이 기절한 경우, LOST 플래그를 세움.-----#
  def NextPokemon(self):
    i = 1
    while i < len(self.pokemon_list):
      if self.pokemon_list[i].get_knocked_out() == True: #마지막 포켓몬이 기절한 경우 Lost = 1.
        if i == (len(self.pokemon_list) - 1):
          self.Lost = True
          print("All of {}'s pokemon fainted!".format(self.name))
          break
        else:
          i += 1
      else: 
        self.current_pokemon = self.pokemon_list[i] # 다음 포켓몬이 살아있으면 그 포켓몬으로 변경
        print("{} changed their pokemon to {}!".format(self.name, self.current_pokemon.name))
        break

#==========] Pokemon Assignment [==========#

#여기에다 CSV에서 포겟몬 4마리씩 뽑아서 Pokemon_List에 설정하는 코드 넣어주세요
#코드 넣으면 밑에 표시한 부분은 지워도 됩니다.
#Pokemon Attribute 순서는 (이름, type1, type2, 체력, 공격, 방어, 전설여부) 로 해주세요.
#포켓몬의 Type2 가 없을경우, None로 설정해주세요.

#모든 타입을 고려하여 상성표를 작성하였기 때문에, 하나의 포켓몬에 두개의 속성이 있어도 처리 가능합니다.
#그런데 문제에서는 물타입, 불타입만 사용하라고 합니다.

#-----일일이 포켓몬 설정. 이부분은 CSV에서 읽어서 무작위로 지정하는 코드로 바꿔주세요
#import pandas as pd

Charmeleon = Pokemon('Charmeleon', 'Fire', 'Flying', 78, 104, 78, False)
Blastoise = Pokemon('Blastoise', 'Water', None, 79, 83, 100, False)
Slowpoke = Pokemon('Slowpoke', 'Water', 'Psychic', 90, 65, 65, False)
Suicune = Pokemon('Suicune', 'Water', None, 100, 75, 115, True)

Emboar = Pokemon('Emboar', 'Fire', 'Fighting', 110, 123, 65, False)
Delphox = Pokemon('Delphox', 'Fire', 'Psychic', 75, 69, 72, False)
Pyroar = Pokemon('Pyroar', 'Fire', 'Normal', 86, 68, 72, False)
Infernape = Pokemon('Infernape', 'Fire', 'Fighting', 76, 104, 71, False)

Ponyta = Pokemon('Ponyta', 'Fire', None, 50, 85, 55, False)
Rapidash = Pokemon('Rapidash', 'Fire', None, 65, 100, 70, False)
Flareon = Pokemon('Flareon', 'Fire', None, 65, 130, 60, False)
Typhlosion = Pokemon('Typhlosion', 'Fire', None, 78, 84, 78, False)

Feraligatr = Pokemon('Feraligatr', 'Water', None, 85, 105, 100, False)
Octillery = Pokemon('Octillery', 'Water', None, 75, 105, 75, False)
Wailord = Pokemon('Wailord', 'Water', None, 170, 90, 45, False)
Kyogre = Pokemon('Kyogre', 'Water', None, 100, 100, 90, True)

Raticate = Pokemon('Raticate', 'Normal', None, 55, 81, 60, False)
Misdreavus = Pokemon('Misdreavus', 'Ghost', None, 60, 60, 60, False)

Politoed = Pokemon('Politoed', 'Water', None, 90, 75, 75, False)
Feebas = Pokemon('Feebas', 'Water', None, 20,15,20,False)
Milotic = Pokemon('Milotic', 'Water', None, 95,60,79,False)
Gorebyss = Pokemon('Gorebyss','Water',None,55,84,105,False)

Slugma = Pokemon('Slugma', 'Fire', None, 40,40,40,None)
Magby = Pokemon('Magby', 'Fire', None, 45,75,37,None)
Magmortar = Pokemon('Magmortar', 'Fire',None,75,95,67,False)
Tepig = Pokemon('Tepig', 'Fire', None, 65,63,45,False)

Pokemon_List_1 = [Charmeleon, Blastoise, Emboar, Delphox] #이 리스트에 무작위로 넣어주세요
Pokemon_List_2 = [Slowpoke, Suicune, Pyroar, Infernape] #여기도요

Pokemon_List_3 = [Ponyta, Rapidash, Flareon, Typhlosion]
Pokemon_List_4 = [Feraligatr, Octillery, Wailord, Kyogre]

Pokemon_List_5 = [Politoed, Feebas, Milotic, Gorebyss]
Pokemon_List_6 = [Slugma, Magby, Magmortar, Tepig]

#-----여기까지요

Trainer_1 = Trainer('Jun', Pokemon_List_1, 3, Pokemon_List_1[0])
Trainer_2 = Trainer('Subaru', Pokemon_List_2, 3, Pokemon_List_2[0])

#==========] Pokemon Battle! [==========#

def PokemonBattle(Trainer_1, Trainer_2): # 실제 포켓몬 배틀을 진행하는 함수.
  print("\n\nPokemon Battle Start!\n\n")

  while(Trainer_1.Lost == False and Trainer_2.Lost == False):
    if Trainer_1.current_pokemon.health <= 20: #포켓몬의 체력이 20 이하가 되면 포션 사용
      if Trainer_1.current_pokemon.health <= 0: #현재 포켓몬이 기절하였을 경우 다음 포켓몬으로 교체
          Trainer_1.NextPokemon()
      elif Trainer_1.potions != 0: 
        Trainer_1.use_potion()
      
      else:
        Trainer_1.attack(Trainer_2) # 포션이 없고 포켓몬이 살아있을 경우 공격
    else:
      Trainer_1.attack(Trainer_2)
  
    if Trainer_1.Lost == True: #모든 포켓몬이 기절했을 때 그 자리에서 배틀을 끝냄.
      break;

    if Trainer_2.current_pokemon.health <= 20: 
      if Trainer_2.current_pokemon.health <= 0: 
          Trainer_2.NextPokemon()
      elif Trainer_2.potions != 0: 
        Trainer_2.use_potion()
      
      else:
        Trainer_2.attack(Trainer_2) 
    else:
      Trainer_2.attack(Trainer_1)

  print("\nBattle End!") # 배틀이 끝나면 승자를 표시
  if Trainer_1.Lost == True:
    print("{} Wins!".format(Trainer_2.name))
  else:
    print("{} Wins!".format(Trainer_1.name))

#---------------------------------------------------

#PokemonBattle(Trainer_1, Trainer_2)
Trainer_F1 = Trainer('Fire2', Pokemon_List_3, 3, Pokemon_List_3[0])
Trainer_F2 = Trainer('Fire1', Pokemon_List_6, 1, Pokemon_List_6[0])
Trainer_W1 = Trainer('Water1', Pokemon_List_4, 1, Pokemon_List_4[0])
Trainer_W2 = Trainer('Water2', Pokemon_List_5, 3, Pokemon_List_5[0])

PokemonBattle(Trainer_F1, Trainer_F2)
