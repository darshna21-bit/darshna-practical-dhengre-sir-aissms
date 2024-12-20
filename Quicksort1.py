def quick_sort(arr):
    """Sorts an array of floating-point numbers using the Quick Sort algorithm."""
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def display_top_five_scores(scores):
    """Displays the top five scores from the sorted array."""
    top_five = scores[-5:]  # Last five elements in the sorted array
    print("Top Five Scores:", top_five[::-1])  # Display in descending order

def main():
    # Input: First-year percentages
    num_students = int(input("Enter the number of students: "))
    percentages = []
    for i in range(num_students):
        score = float(input(f"Enter percentage of student {i+1}: "))
        percentages.append(score)
    
    # Sorting the array
    sorted_percentages = quick_sort(percentages)
    print("Sorted Percentages:", sorted_percentages)
    
    # Displaying top five scores
    display_top_five_scores(sorted_percentages)

# Run the main function
if __name__ == "__main__":
    main()
