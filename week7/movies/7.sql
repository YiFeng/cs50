SELECT m.title, r.rating
FROM movies m, ratings r
WHERE m.id = r.movie_id
AND m.year = 2010
ORDER BY r.rating DESC, m.title ASC;