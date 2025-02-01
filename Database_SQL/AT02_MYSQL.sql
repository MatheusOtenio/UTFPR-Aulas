-- COMANDOS SQL DDL
create table ramo(
cd_ramo int,
ds_ramo varchar(50),
constraint PK_ramo primary key (cd_ramo));
create table tipo(
cd_tipo int,
ds_tipo varchar(50),
constraint PK_tipo primary key (cd_tipo));
create table municipio(
cd_municipio int,
ds_municipio varchar(50),
constraint PK_municipio primary key (cd_municipio));
create table assinante(
cd_assinante int,
nome varchar(50),
cd_ramo int,
cd_tipo int,
constraint PK_assinante primary key (cd_assinante),
constraint FK_assinante1 foreign key (cd_ramo) references
ramo (cd_ramo),
constraint FK_assinante2 foreign key (cd_tipo) references
tipo (cd_tipo));
create table endereco(
cd_endereco int,
ds_endereco varchar(50),
complemento varchar(50),
bairro varchar(50),
CEP varchar(50),
cd_assinante int,
cd_municipio int,
constraint PK_endereco primary key (cd_endereco),
constraint FK_end foreign key (cd_assinante) references
assinante (cd_assinante),
constraint FK_end2 foreign key (cd_municipio) references
municipio (cd_municipio));
create table telefone(
cd_fone int,
ddd varchar(3),
n_fone varchar(10),
cd_endereco int,
constraint PK_telefone primary key (cd_fone),
constraint FK_fone foreign key (cd_endereco) references
endereco (cd_endereco));
-- COMANDOS SQL DML
insert into tipo values (1, 'PREMIUM');
insert into tipo values (2, 'BÁSICO');
insert into tipo values (3, 'GRÁTIS');
insert into tipo values (4, 'RESIDENCIAL');
insert into RAMO values (1, 'INFORMÁTICA');
insert into RAMO values (2, 'MEDICINA');
insert into RAMO values (3, 'COMÉRCIO');
insert into MUNICIPIO values (1, 'APUCARANA');
insert into MUNICIPIO values (2, 'JANDAIA');
insert into MUNICIPIO values (3, 'ARAPONGAS');
insert into MUNICIPIO values (4, 'GUARAPUAVA');
insert into MUNICIPIO values (5, 'FOZ DO IGUAÇU');
INSERT INTO ASSINANTE VALUES (1, 'JOHN', 1, 2);
INSERT INTO ASSINANTE VALUES (2, 'JIMI', 2, 1);
INSERT INTO ASSINANTE VALUES (3, 'PABLO', 2, 1);
INSERT INTO ASSINANTE VALUES (4, 'VALENTINA', 1, 2);
INSERT INTO ASSINANTE VALUES (5, 'ARIANE', 1, 1);
INSERT INTO ENDERECO VALUES (1, 'RUA ABC', 'APTO 201',
'TESTE', '999999-00', 1, 1);
INSERT INTO ENDERECO VALUES (2, 'AV. JK', '', 'TESTE',
'999999-00', 1, 1);
INSERT INTO ENDERECO VALUES (3, 'RUA BRASIL', 'APTO 105',
'CENTRO', '999999-00', 2, 4);
INSERT INTO ENDERECO VALUES (4, 'AV. CURITIBA', 'APTO 53',
'CENTRO', '999999-00', 3, 5);
INSERT INTO ENDERECO VALUES (5, 'AV. CENTRAL', 'APTO 131',
'CENTRO', '999999-00', 4, 2);
INSERT INTO ENDERECO VALUES (6, 'AV. IPIRANGA', 'APTO 131',
'CENTRO', '999999-00', 5, 3);
INSERT INTO TELEFONE VALUES (1, '43', '9999999999', 1);
INSERT INTO TELEFONE VALUES (2, '43', '9999999999', 5);
INSERT INTO TELEFONE VALUES (3, '43', '9999999999', 6);
INSERT INTO TELEFONE VALUES (4, '43', '9999999999', 2);


--==========================================================================//


mysql> SELECT
-> assinante.nome AS nm_assinante,
-> tipo.ds_tipo
-> FROM
-> assinante
-> INNER JOIN
-> tipo
-> ON
-> assinante.cd_tipo = tipo.cd_tipo;
+--------------+---------+
| nm_assinante | ds_tipo |
+--------------+---------+
| JIMI | PREMIUM |
| PABLO | PREMIUM |
| ARIANE | PREMIUM |
| JOHN | BÁSICO |
| VALENTINA | BÁSICO |
+--------------+---------+

--==========================================================================//


mysql> SELECT
 -> assinante.nome AS nm_assinante,
 -> tipo.ds_tipo
 -> FROM
 -> assinante
 -> NATURAL JOIN
 -> tipo;
+--------------+---------+
| nm_assinante | ds_tipo |
+--------------+---------+
| JIMI | PREMIUM |
| PABLO | PREMIUM |
| ARIANE | PREMIUM |
| JOHN | BÁSICO |
| VALENTINA | BÁSICO |
+--------------+---------+


--==========================================================================//


mysql> SELECT
 -> assinante.nome AS nm_assinante,
 -> ramo.cd_ramo,
 -> ramo.ds_ramo
 -> FROM
 -> assinante
 -> INNER JOIN
 -> ramo
 -> ON
 -> assinante.cd_ramo = ramo.cd_ramo
 -> WHERE
 -> ramo.ds_ramo != 'COMÉRCIO';
+--------------+---------+-------------+
| nm_assinante | cd_ramo | ds_ramo |
+--------------+---------+-------------+
| JOHN | 1 | INFORMÁTICA |
| VALENTINA | 1 | INFORMÁTICA |
| ARIANE | 1 | INFORMÁTICA |
| JIMI | 2 | MEDICINA |
| PABLO | 2 | MEDICINA |
+--------------+---------+-------------+


--==========================================================================//


mysql> SELECT
 -> assinante.nome AS nm_assinante,
 -> ramo.ds_ramo,
 -> tipo.ds_tipo
 -> FROM
 -> assinante
 -> INNER JOIN
 -> ramo
 -> ON
 -> assinante.cd_ramo = ramo.cd_ramo
 -> INNER JOIN
 -> tipo
 -> ON
 -> assinante.cd_tipo = tipo.cd_tipo;
+--------------+-------------+---------+
| nm_assinante | ds_ramo | ds_tipo |
+--------------+-------------+---------+
| JOHN | INFORMÁTICA | BÁSICO |
| VALENTINA | INFORMÁTICA | BÁSICO |
| ARIANE | INFORMÁTICA | PREMIUM |
| JIMI | MEDICINA | PREMIUM |
| PABLO | MEDICINA | PREMIUM |
+--------------+-------------+---------+


--==========================================================================//

  
mysql> SELECT
 -> assinante.nome AS nm_assinante,
 -> ramo.ds_ramo,
 -> tipo.ds_tipo
 -> FROM
 -> assinante
 -> INNER JOIN
 -> ramo
 -> ON
 -> assinante.cd_ramo = ramo.cd_ramo
 -> INNER JOIN
 -> tipo
 -> ON
 -> assinante.cd_tipo = tipo.cd_tipo
 -> WHERE
 -> assinante.cd_assinante = 1;
+--------------+-------------+---------+
| nm_assinante | ds_ramo | ds_tipo |
+--------------+-------------+---------+
| JOHN | INFORMÁTICA | BÁSICO |
+--------------+-------------+---------+


--==========================================================================//


mysql> SELECT
 -> assinante.cd_assinante,
 -> assinante.nome AS nm_assinante,
 -> tipo.ds_tipo
 -> FROM
 -> assinante
 -> LEFT JOIN
 -> tipo
 -> ON
 -> assinante.cd_tipo = tipo.cd_tipo;
+--------------+--------------+---------+
| cd_assinante | nm_assinante | ds_tipo |
+--------------+--------------+---------+
| 1 | JOHN | BÁSICO |
| 2 | JIMI | PREMIUM |
| 3 | PABLO | PREMIUM |
| 4 | VALENTINA | BÁSICO |
| 5 | ARIANE | PREMIUM |
+--------------+--------------+---------+


--==========================================================================//


mysql> SELECT
 -> tipo.cd_tipo,
 -> tipo.ds_tipo,
 -> assinante.nome AS nm_assinante
 -> FROM
 -> assinante
 -> RIGHT JOIN
 -> tipo
 -> ON
 -> assinante.cd_tipo = tipo.cd_tipo;
+---------+-------------+--------------+
| cd_tipo | ds_tipo | nm_assinante |
+---------+-------------+--------------+
| 1 | PREMIUM | JIMI |
| 1 | PREMIUM | PABLO |
| 1 | PREMIUM | ARIANE |
| 2 | BÁSICO | JOHN |
| 2 | BÁSICO | VALENTINA |
| 3 | GRÁTIS | NULL |
| 4 | RESIDENCIAL | NULL |
+---------+-------------+--------------+


--==========================================================================//


mysql> SELECT
 -> tipo.cd_tipo,
 -> tipo.ds_tipo,
 -> assinante.nome AS nm_assinante
 -> FROM
 -> tipo
 -> LEFT JOIN
 -> assinante
 -> ON
 -> tipo.cd_tipo = assinante.cd_tipo;
+---------+-------------+--------------+
| cd_tipo | ds_tipo | nm_assinante |
+---------+-------------+--------------+
| 1 | PREMIUM | JIMI |
| 1 | PREMIUM | PABLO |
| 1 | PREMIUM | ARIANE |
| 2 | BÁSICO | JOHN |
| 2 | BÁSICO | VALENTINA |
| 3 | GRÁTIS | NULL |
| 4 | RESIDENCIAL | NULL |
+---------+-------------+--------------+


--==========================================================================//


mysql> SELECT
 -> assinante.nome AS nm_assinante,
 -> tipo.ds_tipo
 -> FROM
 -> assinante
 -> INNER JOIN
 -> tipo
 -> ON
 -> assinante.cd_tipo = tipo.cd_tipo
 -> INNER JOIN
 -> endereco
 -> ON
 -> assinante.cd_assinante = endereco.cd_assinante
 -> INNER JOIN
 -> municipio
 -> ON
 -> endereco.cd_municipio = municipio.cd_municipio
 -> WHERE
 -> municipio.ds_municipio = 'FOZ DO IGUAÇU'
 -> OR tipo.ds_tipo = 'BÁSICO';
+--------------+---------+
| nm_assinante | ds_tipo |
+--------------+---------+
| PABLO | PREMIUM |
| JOHN | BÁSICO |
| JOHN | BÁSICO |
| VALENTINA | BÁSICO |
+--------------+---------+

--==========================================================================//


mysql> SELECT
 -> assinante.nome AS nm_assinante,
 -> telefone.n_fone
 -> FROM
 -> assinante
 -> INNER JOIN
 -> tipo
 -> ON
 -> assinante.cd_tipo = tipo.cd_tipo
 -> INNER JOIN
 -> endereco
 -> ON
 -> assinante.cd_assinante = endereco.cd_assinante
 -> INNER JOIN
 -> municipio
 -> ON
 -> endereco.cd_municipio = municipio.cd_municipio
 -> INNER JOIN
 -> telefone
 -> ON
 -> endereco.cd_endereco = telefone.cd_endereco
 -> WHERE
 -> tipo.ds_tipo = 'COMERCIAL'
 -> AND (municipio.ds_municipio = 'APUCARANA' OR municipio.ds_municipio =
'GUARAPUAVA');
