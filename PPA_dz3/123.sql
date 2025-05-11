SELECT loginid FROM humanresources.employee WHERE gender = 'M';

SELECT city, stateprovince.name
FROM person.address
INNER JOIN person.stateprovince
ON person.stateprovince.stateprovinceid = person.address.stateprovinceid;

SELECT salesterritory.name FROM sales.salesterritory GROUP BY saleslastyear, name HAVING saleslastyear > 4000000;