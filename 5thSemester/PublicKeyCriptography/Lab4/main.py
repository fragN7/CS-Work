import random
import sympy


def gcd(a, b):

    if b == 0:
        return a
    else:
        return gcd(b, a % b)


def rsa(alphabet, k, l, n, e, text):

    # split a text into blocks of k symbols and add space if necessary
    blocks = []
    for i in range(0, len(text), k):
        blocks.append(text[i:i + k])
    if len(blocks[-1]) < k:
        blocks[-1] += ' ' * (k - len(blocks[-1]))
    print(blocks)

    # convert blocks into numbers
    numbers = []
    for block in blocks:
        number = 0
        for index, symbol in enumerate(block):
            number += alphabet.index(symbol) * (27 ** (k - index - 1))  # alph(index) * 27^ (k-index-1)
        numbers.append(number)
    print(numbers)

    # encrypt/decrypt based on e (public/private key)
    encrypted_numbers = []
    for number in numbers:
        encrypted_numbers.append(pow(number, e, n))  # number^e mod n
    print(encrypted_numbers)

    # transform encrypted numbers into blocks of l symbols
    encrypted_blocks = []
    for number in encrypted_numbers:
        block = ''
        for i in range(l):
            block = alphabet[number % 27] + block
            number //= 27
        encrypted_blocks.append(block)
    print(encrypted_blocks)

    # transform blocks into text
    encrypted_text = ''
    for block in encrypted_blocks:
        encrypted_text += block
    return encrypted_text


def generate_key():
    # Generate random prime numbers for p and q
    p = random.choice(list(sympy.primerange(2, 100)))
    q = random.choice(list(sympy.primerange(2, 100)))

    n = p * q
    fi_n = (p - 1) * (q - 1)

    e = 3
    while gcd(e, fi_n) != 1:
        e += 2

    return n, e, fi_n

def encrypt(n, e, fi_n):
    alphabet = ' abcdefghijklmnopqrstuvwxyz'
    k = 2  # number of symbols in a block of plaintext
    l = 3  # number of symbols in a block of ciphertext

    print("Randomly generated public key:")
    print("n=", n, "e=", e)

    while True:
        text = input("Enter plaintext (only lowercase alphabets): ")
        if all(symbol in alphabet for symbol in text) and text.islower():
            break
        else:
            print("Invalid input. Please enter only lowercase alphabets.")

    encrypted_text = rsa(alphabet, k, l, n, e, text)
    print("Encrypted text:", encrypted_text)


def decrypt(n, e, fi_n):
    alphabet = ' abcdefghijklmnopqrstuvwxyz'
    k = 2  # number of symbols in a block of plaintext
    l = 3  # number of symbols in a block of ciphertext

    d = pow(e, -1, fi_n)

    print("Randomly generated private key:")
    print("n=", n, "d=", d)

    while True:
        text = input("Enter plaintext (only lowercase alphabets): ")
        if all(symbol in alphabet for symbol in text) and text.islower():
            break
        else:
            print("Invalid input. Please enter only lowercase alphabets.")

    decrypted_text = rsa(alphabet, l, k, n, d, text)
    print("Decrypted text:", decrypted_text)


if __name__ == '__main__':
    n, e, fi_n = generate_key()
    encrypt(n, e, fi_n)
    decrypt(n, e, fi_n)