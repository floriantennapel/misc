n = int(input())

for _ in range(n):
    words = input().strip().split()
    not_fox = set()
    if words is None:
        break
    while True:
        animal = input().strip()
        if animal == 'what does the fox say?':
            for w in words:
                if w not in not_fox:
                    print(w, end=' ')
            break
        not_fox.add(animal.split()[-1]) 






