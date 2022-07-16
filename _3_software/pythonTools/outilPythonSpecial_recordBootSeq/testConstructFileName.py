import time

def main():
    '''
    Main program function
    '''
    print("Hello")
    timestr = time.strftime("%Y%m%d-%H%M%S")
    print(timestr)
    filename= "bootSep_ioteps_" + time.strftime("%Y%m%d-%H%M%S") + ".txt"
    print(filename)


if __name__ == "__main__":
    main()