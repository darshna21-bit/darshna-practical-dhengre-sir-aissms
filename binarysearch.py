def binary_search_recursive(phonebook, low, high, name):
    if high >= low:
        mid = (low + high) // 2
        if phonebook[mid][0] == name:
            return mid
        elif phonebook[mid][0] > name:
            return binary_search_recursive(phonebook, low, mid - 1, name)
        else:
            return binary_search_recursive(phonebook, mid + 1, high, name)
    return -1

def binary_search_iterative(phonebook, name):
    low, high = 0, len(phonebook) - 1
    while low <= high:
        mid = (low + high) // 2
        if phonebook[mid][0] == name:
            return mid
        elif phonebook[mid][0] > name:
            high = mid - 1
        else:
            low = mid + 1
    return -1

def main():
    # Initialize phonebook
    phonebook = []
    
    # Add friends to phonebook
    n = int(input("Enter the number of friends: "))
    for _ in range(n):
        name = input("Enter friend's name: ")
        mobile = input("Enter friend's mobile number: ")
        phonebook.append((name, mobile))
    
    # Sort phonebook by name
    phonebook.sort()

    # Search for a friend
    search_name = input("Enter the name to search: ")
    
    # Recursive binary search
    idx_recursive = binary_search_recursive(phonebook, 0, len(phonebook) - 1, search_name)
    if idx_recursive != -1:
        print(f"Found {search_name} (Recursive) with number {phonebook[idx_recursive][1]}")
    else:
        print(f"{search_name} not found (Recursive). Adding to phonebook.")
        new_mobile = input(f"Enter mobile number for {search_name}: ")
        phonebook.append((search_name, new_mobile))
        phonebook.sort()

    # Iterative binary search
    idx_iterative = binary_search_iterative(phonebook, search_name)
    if idx_iterative != -1:
        print(f"Found {search_name} (Iterative) with number {phonebook[idx_iterative][1]}")
    else:
        print(f"{search_name} not found (Iterative).")

    # Print updated phonebook
    print("\nUpdated Phonebook:")
    for entry in phonebook:
        print(f"{entry[0]}: {entry[1]}")

if __name__ == "__main__":
    main()
