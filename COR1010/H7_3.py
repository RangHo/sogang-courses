words = [
    'courtyard',
    'alley',
    'landlady',
    'landlord',
    'tenant',
    'stairs',
    'fire escape',
    'trash bin',
    'hallway',
    'balcony',
    'doorknob',
    'peephole',
    'elevator',
    'lobby',
    'door chain',
    'realtor'
]

word_dict = {}

for word in words:
    start = word[0]
    if word_dict.get(start, False):
        word_dict[start].append(word)
    else:
        word_dict[start] = [word]

for letter, words in word_dict.items():
    plural_noun = "s"
    plural_verb = ""
    if len(words) == 1:
        plural_noun, plural_verb = plural_verb, plural_noun

    print("{} word{} start{} with '{}'".format(
        words, plural_noun, plural_verb, letter
    ))
