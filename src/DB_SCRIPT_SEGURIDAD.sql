create database if not exists Amazin;
use Amazin;
Create table if not exists User(
	id int not null auto_increment,
    username varchar(25) not null unique,
    password_hash varchar(40) not null,
    fullname varchar(70) not null,
    email varchar(50) not null unique,
    phone_number int not null unique,
    PRIMARY KEY(id)
);

create table if not exists Product(
    id int not null auto_increment,
    price int not null,
    product_name varchar(70) not null,
    product_descp varchar(2000) not null,
    seller_fk int not null,
    buyer_fk int,
    bill_id int,
    product_status BOOLEAN not null default 0,
    primary key (id),
    foreign key (seller_fk) references User (id)
);

create table if not exists Cart(
    user_fk int not null,
    product_fk int not null,
    foreign key (user_fk) references User(id),
    foreign key (product_fk) references Product (id),
    primary key (user_fk, product_fk)
);

create table if not exists Claim(
    id int not null auto_increment,
    title varchar(90) not null,
    claim_type int not null,
    msg varchar(2000) not null,
    msg_timestamp DATE not null,
    reply_to_claim_fk int,
    user_fk int,
    primary key (id),
    foreign key (reply_to_claim_fk) references Claim (id),
    foreign key (user_fk) references User (id)
);

create table if not exists Bill_Info(
    id int not null auto_increment,
    user_fk int not null,
    credit_card varchar(16) not null,
    amount int not null,
    bill_date DATE not null,
    foreign key (user_fk) references User(id),
    primary key (id)
);

create table _Session(
    id varchar(24) unique not null,
    user_fk int unique not null,
    session_expiration DATE not null,
    FOREIGN KEY (user_fk) REFERENCES User(id),
    PRIMARY KEY (id)
); 