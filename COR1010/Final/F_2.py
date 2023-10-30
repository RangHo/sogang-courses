def readWord(filename: str) -> list:
    """Read the given file into a list of words.

    :param str filename: The name of the file to read.
    :return: A list of words.
    :rtype: list
    """

    # Open the file, read into lines, and strip each line
    with open(filename, "r") as f:
        words = [line.strip() for line in f]

    # Return the result
    return words


def printDic(dic: dict[str, set]) -> None:
    """Print the given dictionary with proper format.

    :param dict dic: The dictionary to print.
    :return: None
    :rtype: None
    """

    # Print the dictionary
    for first_letter, word in dic.items():
        print(f"{word} starts with '{first_letter}'")


word_dic = {}
words = readWord("vocabulary.txt")

# Iterate through each word
for word in words:
    first_letter = word[0]

    # If the first letter is not in the dictionary, add it;
    # else, create a new set
    if first_letter in word_dic:
        word_dic[first_letter].add(word)
    else:
        word_dic[first_letter] = {word}

# Print the dictionary
printDic(word_dic)
