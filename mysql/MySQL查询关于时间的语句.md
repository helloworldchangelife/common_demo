###MySQL查询关于最近时间的语句：

1、查询当天的数据
select * from  表名 where TO_DAYS(时间字段)=TO_DAYS(NOW());
2、查询当周的数据
select * from  表名 where YEARWEEK(DATE_FORMAT(时间字段,'%Y-%m-%d'))=YEARWEEK(NOW());
3、查询当月的数据
select * from  表名 where DATE_FORMAT(时间字段,'%Y%m')=DATE_FORMAT(CURDATE(),'%Y%m');
4、查询昨天的数据
select * from 表名 where TO_DAYS(NOW())-TO_DAYS(时间字段）=1;
5、查询最近7天的数据
select * from 表名 where DATE_SUB(CURDATE(),INTERVAL 7 DAY)<=DATE(时间字段);
6、查询当年的数据
select * from 表名 where YEAR(时间字段) =YEAR(NOW());
7、查询上周的数据
select * from 表名 whereYEARWEEK(DATE_FORMAT(时间字段,'%Y-%m-%d'))=YEARWEEK(NOW())-1;
8、查询上月的数据
select *from 表名 where PERIOD_DIFF(DATE_FORMAT(NOW(),'%Y%m'),DATE_FORMAT(时间字段,'%Y%m'))=1;