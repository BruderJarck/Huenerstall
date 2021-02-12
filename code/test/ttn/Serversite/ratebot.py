import random


def testezahl(zahl, ratezahl):
    if zahl < ratezahl:
        ans = "kleiner"
    elif zahl > ratezahl:
        ans = "größer"
    else:
        ans = "gleich"
    return ans


def main():
    while True:
        try:
            ratezahl = int(input("bitte ratezahl eingeben zwischen 0 und 100\n>"))
            zahl = random.randint(0, 100)
            counter = 0
            print(ratezahl, zahl)
            while True:
                counter += 1
                a = testezahl(zahl, ratezahl)
                print(zahl, a)
                if a == "kleiner":
                    zahl = int(((100 - zahl) / 2) + zahl)
                elif a == "größer":
                    zahl = int(zahl / 2 - 1)
                elif a == "gleich":
                    print("erraten!, Ergebnis", zahl, "versuche: ", counter)
                    break
                else:
                    pass
                # print(zahl, a)
        except ValueError:
            print("das ist keinezahl")


if __name__ == '__main__':
    print("starte ratebot")
    main()
    # print(testezahl(50, 50))
    # print(testezahl(50, 100))
    # print(testezahl(75, 50))
