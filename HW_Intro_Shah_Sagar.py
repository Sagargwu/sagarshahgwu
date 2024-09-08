HW_Intro_Shah_Sagar.py

# Question 1: Explanation about yourself (commented out as it's not executable code)
# My name is [Your Name], and I am currently pursuing a degree in data science at George Washington University.
# I am passionate about data analysis and solving real-world problems through technology.
# In my spare time, I enjoy learning new skills and working on projects related to artificial intelligence.
# I also love participating in data competitions. One of my favorite websites for this is Kaggle (https://www.kaggle.com),
# where you can learn data science and participate in real-world competitions.

# Question 2: Create a list of class titles in the data science program
myCourseTitles = [
    "Intro to Data Mining",
    "EAP",
    "Intro to Data Science",
    "Intro to Data Warehousing",
]

# Print the last entry in the list
print("Last entry in myCourseTitles list:", myCourseTitles[-1])

# Question 3: Replace "Intro to Data Warehousing" with "Intro to Data Minng"
myCourseTitles[-1] = "Intro to Data Mining"
print("Updated myCourseTitles list:", myCourseTitles)

# Question 4: Create a Python dictionary of the classes with course numbers
myCourseList = {
    "DATS_6103_10": "Intro to Data Mining",
    "EAP_6110_10": "EAP",
    "DATS_6101_11": "Intro to Data Science",
    "DATS_6102_12": "Intro to Data Warehousing",
}

print("Dictionary of course titles with course numbers:", myCourseList)

# Question 5: Print out the number of classes you plan to take
print("Number of classes planned:", len(myCourseList))

# Question 6: Convert the list of Course Titles to a tuple and print the second half
myTupleCourseTitles = tuple(myCourseTitles)
second_half = myTupleCourseTitles[len(myTupleCourseTitles) // 2:]
print("Second half of myTupleCourseTitles:", second_half)

# Question 7: Create an object (JSON-like dictionary) about yourself
myself = {
    "Firstname": "Sagar",
    "Lastname": "Shah",
    "CompletedClasses": [
        {
            "CourseNumber": "DATS_6103_10",
            "CourseTitle": "Intro to Data Mining",
            "Prerequsites": [],
            "Year": 2024,
            "Semester": "Fall",
            "Instructor": "Prof. Ning Rui"
        }
    ],
    "InProgressClasses": [
        {
            "CourseNumber": "EAP_6110_10",
            "CourseTitle": "EAP",
            "Prerequsites": [
                {
                    "CourseNumber": "DATS_6101_11",
                    "CourseTitle": "Intro to Data Science",
                    "Prerequsites": []
                }
            ],
            "Year": 2024,
            "Semester": "Fall",
            "Instructor": "Prof. Darcy Morris"
        }
    ],
    "PlannedClasses": [
        {
            "CourseNumber": "DATS_6102_12",
            "CourseTitle": "Intro to Data Wareshousing",
            "Prerequsites": [

            ]
        }
    ],
    "ExpectedGraduationYear": 2025
}

print("Myself JSON-like object:", myself)

# Question 8: Make a copy of your info for a friend
friend_info = myself.copy()

# Ensure changes to friend's info don't affect yours
friend_info["Firstname"] = "X"
friend_info["Lastname"] = "Y"

print("Friend's info:", friend_info)
print("Original info (unchanged):", myself)
