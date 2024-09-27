from itertools import product

while len(input().split()) != 1:
    front = [int(d) for d in input().split()]
    rear = [int(d) for d in input().split()]

    ratios = [r / f for f, r in product(front, rear)]
    ratios.sort()

    max_spread = max(d2 / d1 for d1, d2 in zip(ratios, ratios[1:]))
    print(f'{max_spread:.2f}')