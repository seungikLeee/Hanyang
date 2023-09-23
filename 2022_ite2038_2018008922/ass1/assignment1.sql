select name 
from Pokemon 
where Pokemon.type = 'Grass' 
order by name asc;

select name 
from Trainer 
where Trainer.hometown = 'Brown City' or Trainer.hometown = 'Rainbow City' 
order by name asc;

select distinct type 
from Pokemon 
order by type asc;

select name 
from city 
where name like 'B%' 
order by name asc;

select hometown 
from Trainer 
where Trainer.name not like 'M%' 
order by hometown asc;

select nickname 
from catchedpokemon 
where level = (select max(catchedpokemon.level) 
from catchedpokemon) 
order by nickname asc;

select name 
from pokemon 
where pokemon.name like 'A%' or pokemon.name like 'E%' or pokemon.name like 'I%' or pokemon.name like 'O%' or pokemon.name like 'U%' 
order by name asc;

select avg(Level) as "Average Level" 
from catchedpokemon;

select Max(level) 
from catchedpokemon 
where catchedpokemon.owner_id = (select id 
from trainer 
where trainer.name = 'Yellow');

select distinct hometown 
from Trainer 
order by hometown asc;

with A_pokemon(nickname, id) as (select nickname, owner_id  
from catchedpokemon  
where nickname like 'A%' 
group by nickname) 
select name, nickname 
from trainer, A_pokemon 
where trainer.id = A_pokemon.id  
order by name asc;

select name 
from trainer 
where id = (select leader_id 
from gym 
where (select name 
from city 
where city.description = 'Amazon')=gym.city);

with Fire(pokemon_id, trainer_id) as (select catchedpokemon.pid, catchedpokemon.owner_id  
from pokemon, catchedpokemon 
where pokemon.id = catchedpokemon.pid and pokemon.type = 'Fire'
group by pokemon.id)
,
Result(id, num) as (select distinct trainer_id as N, (select count(*) from Fire where N = trainer_id) 
from Fire
group by trainer_id)
select id, num as countFire
from Result
where num = (select max(num) from Result);

select distinct type
from pokemon
where id < 10
order by id desc;

select count(id) as count
from pokemon
where type not in (select type from pokemon where type = 'Fire'); 

select name
from pokemon
where id = (select before_id from evolution where after_id < before_id)
order by name asc;

with water_pokemon(id,level) as (select pokemon.id, catchedpokemon.level 
from pokemon,catchedpokemon 
where pokemon.id = catchedpokemon.pid and pokemon.type = 'Water')
select avg(level)
from water_pokemon;

with leader_pokemon(l_id, level, nickname) as (select gym.leader_id, catchedpokemon.level, catchedpokemon.nickname 
from gym, catchedpokemon 
where gym.leader_id = catchedpokemon.owner_id)
select nickname
from leader_pokemon
where level = (select max(level) from leader_pokemon);

with Blue(t_name, level) as (select trainer.name, catchedpokemon.level 
from trainer, catchedpokemon 
where trainer.id = catchedpokemon.owner_id and trainer.hometown = 'Blue City')
,
Result(name , avg) as (select distinct Blue.t_name as N, (select avg(level) from Blue where N = Blue.t_name) 
from Blue)  
select name
from Result
where avg = (select max(avg) from Result); 

with home(hometown, num) as (select hometown as N, (select count(hometown) from trainer where N = hometown) 
from trainer)
,
s_trainer(t_id) as (select id 
from trainer, home
where trainer.hometown = home.hometown and home.num=1)
,
can_evol_Elec(p_name, p_id) as (select name, id 
from pokemon,evolution 
where type = 'Electric' and id in (select before_id from evolution))   
select distinct p_name
from catchedpokemon, can_evol_Elec, s_trainer 
where t_id = owner_id and pid = p_id
order by p_name asc;

with leader(l_name, p_level) as (select name, level 
from trainer,gym,catchedpokemon
where gym.leader_id = trainer.id and gym.leader_id = catchedpokemon.owner_id)
select distinct l_name as N, (select sum(p_level)  
from leader 
where N = leader.l_name) as sumLevel 
from leader
order by sumLevel desc;  

with home_trainer(home_name, t_num) as (select distinct hometown as N, (select count(hometown) from trainer where N = hometown)
from trainer)
select home_name
from home_trainer
where t_num = (select max(t_num) from home_trainer); 

with sangnok(sn_p_id) as (select pid 
from trainer,catchedpokemon 
where hometown = 'Sangnok City' and trainer.id = owner_id)
,
brown(b_p_id) as (select pid 
from trainer,catchedpokemon 
where hometown = 'Brown City' and trainer.id = owner_id)
,
catched_s_b(p_id) as (select distinct pid 
from catchedpokemon,sangnok,brown
where pid = sn_p_id and pid = b_p_id)  
select name 
from pokemon,catched_s_b 
where p_id = pokemon.id
order by name asc;

with p_catched(p_owner_id) as (select owner_id 
from pokemon,catchedpokemon 
where name like 'P%' and pokemon.id = pid)
select name
from p_catched, trainer
where p_owner_id = id and hometown = 'Sangnok City'
order by name asc;

select trainer.name as t_name, pokemon.name as p_name 
from trainer, catchedpokemon, pokemon
where trainer.id = catchedpokemon.owner_id and catchedpokemon.pid = pokemon.id
order by t_name asc, p_name asc;

select name
from pokemon
where id in (select before_id
from evolution
where after_id not in (select before_id from evolution) 
and before_id not in (select after_id from evolution))
order by name asc; 

select nickname
from catchedpokemon,pokemon,gym
where type = 'Water' and leader_id = owner_id and pid = pokemon.id and city = 'Sangnok City'
order by nickname asc;

with evol(t_id, p_id) as (select owner_id, pid 
from catchedpokemon 
where pid in (select after_id from evolution))
,
Result(id, num) as (select distinct t_id as N, (select count(p_id) from evol where N = t_id) 
from evol)
select name
from trainer,Result
where Result.id = trainer.id and num >= 3
order by name asc;   

select name
from pokemon
where id not in (select pid from catchedpokemon)
order by name asc;

with tab(home, maxLevel) as 
(select distinct hometown as N, (select max(level) from trainer,catchedpokemon 
where N = trainer.hometown and trainer.id = owner_id)
from trainer)
select maxLevel
from tab
order by maxLevel desc; 

with three_evol(first_id, second_id, third_id) as (select before_id, after_id as N, (select after_id from evolution where N = before_id) 
from evolution 
where after_id in (select before_id from evolution))
,
Result(id, firstName, secondName, thirdName) as (select first_id as N , 
(select name from three_evol,pokemon where N = first_id and pokemon.id = first_id),
(select name from three_evol,pokemon where N = first_id and pokemon.id = second_id),
(select name from three_evol,pokemon where N = first_id and pokemon.id = third_id) 
from three_evol)
select *
from Result
order by id asc;







