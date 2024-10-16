from sys import stdin

input()
text = input().strip().split()
input()

d = dict((a, b) for a, b in (line.strip().split() for line in stdin))
print(' '.join(d[w] for w in text))
