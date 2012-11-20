DROP TABLE IF EXISTS author;
DROP TABLE IF EXISTS book;

CREATE TABLE author 
( 
   id INTEGER PRIMARY KEY,
   firstname VARCHAR(40) NOT NULL,
   surname VARCHAR(40) NOT NULL
);

CREATE TABLE book 
( 
  id INTEGER PRIMARY KEY,
  title VARCHAR(40),
  price REAL,
  authorid INTEGER,
  notes VARCHAR(255) 
);

INSERT INTO author( id, firstname, surname ) VALUES ( 1, "Jesper", "Pedersen" );
INSERT INTO author( id, firstname, surname ) VALUES ( 2, "Kalle Mathias", "Dalheimer" );
INSERT INTO author( id, firstname, surname ) VALUES ( 3, "Bjarne", "Stroustrup");
INSERT INTO author( id, firstname, surname ) VALUES ( 4, "Scott", "Meyers" );

INSERT INTO book( id, title, price, authorid, notes) VALUES ( 1, "Sams Teach Yourself Emacs in 24 Hours", 24.99, 1, "Good book" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 2, "Practical Qt", 45.00, 1, "Learn Amazing Qt Techniques" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 3, "Running Linux", 31.96, 2, "" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 4, "Programming with Qt (1. ed)", 26.36, 2, "" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 5, "Programming with Qt (2. ed)", 39.95, 2, "" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 6, "The C++ Programming Language SE.", 59.95, 3, "Special Edition" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 7, "The C++ Programming Language", 47.66, 3, "" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 8, "The Annotated C++ Reference Manual", 55.95, 3, "" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 9, "The Design and Evolution of C++", 34.95, 3, "" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 10, "Effective C++", 37.95, 4, "" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 11, "More Effective C++", 39.95, 4, "" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 12, "Effective C++ Cd", 29.95, 4, "" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 13, "Effective C++ (50 ways)", 39.95, 4, "" );
INSERT INTO book( id, title, price, authorid, notes) VALUES ( 14, "Effective STL", 39.99, 4, "" );
