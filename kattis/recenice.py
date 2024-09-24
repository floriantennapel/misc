hundreds = ['', 'onehundred', 'twohundred', 'threehundred', 'fourhundred', 'fivehundred', 'sixhundred', 'sevenhundred', 'eighthundred', 'ninehundred']
tens = ['', '', "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]
ones = ['', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', 'ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen']

h = 0
t = 0
o = 1

nums = []

for i in range(1, 1000):
    h = i // 100
    t = (i // 10) % 10
    o = i % 10

    if t == 1:
        s = hundreds[h] + ones[i % 100]
    else:
        s = hundreds[h] + tens[t] + ones[o]
    
    nums.append((s, len(s)))


num_ind = None
words = []
chars = 0

n = int(input())
for i in range(n):
    w = input().strip()
    if w == '$':
        num_ind = i
        words.append(None)
    else:
        words.append(w)
        chars += len(w)

for i, (n, l) in enumerate(nums):
    if chars + l == i+1:
        words[num_ind] = n
        break

for w in words:
    print(w, end=' ')
print()