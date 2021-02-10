from pyswip import Prolog

prolog = Prolog()
prolog.consult('bucket_refill.pl')


while True:
    limits = input("Enter jar limits. It should be a comma-separated or space-separated list of positive integers\n")
    limits = limits.replace(',', ' ')
    limits = limits.strip().split()
    limits = list(map(int, limits))
    goal = int(input("""Enter target volume of water\n""").strip())
    print("Calculating...")
    if any(True for _ in prolog.query(f'solve_silent({limits}, {goal})')):
        print("It's possible! See solution:")
        next(prolog.query(f'solve({limits}, {goal})'))
    else:
        print("It's impossible :(")

    print()