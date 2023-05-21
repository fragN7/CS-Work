from src.code_runners import verify_number, generate_random, verify_runners_codes
import time


def run_main():
    x = generate_random()
    start = time.time()
    while time.time() - start < 60:
            cmd = input("Please write your number here: ")
            try:
                cmd = int(cmd)
            except ValueError:
                print("You have lost")
                return
            if not verify_number(cmd) and cmd != 8086:
                print("You have lost")
                return
            if cmd == x:
                print("You have won")
                return
            elif cmd == 8086:
                print(x)
            else:
                a = verify_runners_codes(x, cmd)[0]
                b = verify_runners_codes(x, cmd)[1]
                print(f"Computer reports {a} codes and {b} runners")
    if time.time() - start > 60:
        print("Time is up, you have lost")


run_main()
