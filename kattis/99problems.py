def closest99(n):
    if len(str(n)) < 3:
        return 99
    
    hundredth = int(n / 100)
    over = hundredth*100 + 99
    under = (hundredth - 1)*100 + 99
    
    if abs(n - under) < abs(n - over):
        return under
    else:
        return over

print(closest99(int(input())))
