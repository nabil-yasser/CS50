# Forensic data recovery from any storage unit
#### Video Demo:  N/A
#### Description:
Concepts used:

- FILE pointers
- pointers
- buffers
- for loops
- while loops
- if statements

## How the webpage works?

The idea is simple. The user can launch the program by typing it's name and filename of forensic image:

- ./recovery filename.raw

This allows you to access program features and start recovering all deleted images.

For teachers, teacher dashboard is unlocked, where they can create a homework and see student's which submitted homework. When accessing the homework, teacher can download the submitted file and then write a review and grade it.

### Routing

Each route checks if the user is authenticated. It means if correct mail and password were supplied and what role it has. So for example a teacher cannot enter /students/homeworks/1 route. The same is for student, he cannot enter teacher dashboard route.

### Sessions

The webpage uses sessions to confirm that user is registered. Once the user logins, his credentials are checked with bcrypt and Passport JS library. Once everything passes a session is created (serialized and deserialized) and stored in the cookies. The server attaches user to subsequent requests, so the back-end can easily access the details, like roles: student, teacher.

### Database

Database stores all users, homework, student submissions. The tables, like student submissions uses foreign keys to relate users to submitted homework. Moreover, homework table uses foreign keys to relate the homework to a teacher.

## Possible improvements

As all applications this one can also be improved. Possible improvements:

- Have administrator account which confirms user identity, so that student could not register as a teacher
- Ability to change account details
- Have a way for teacher to upload videos to explain the assignment
- Notificaitons to email about new homeworks or submissions