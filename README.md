# Implementation of redis

Redis (Remote Dictionary Server) is an in-memory data structure project implementing a distributed, in-memory key-value database with optional durability. Redis supports different kinds of abstract data structures, such as strings, lists, maps, sets, sorted sets, HyperLogLogs, bitmaps, streams, and spatial indexes.

A working implementation of redis with some basic functionalities like

1. GET ( https://redis.io/commands/get )
2. SET ( https://redis.io/commands/set )
3. EXPIRE ( https://redis.io/commands/expire )
4. ZADD ( https://redis.io/commands/zadd )
5. ZRANK ( https://redis.io/commands/zrank )
6. ZRANGE ( https://redis.io/commands/zrange )

### Executable Commands

Everthing should be entered without quotes-

1. SET <key> <value>
2. GET <key>
3. EXPIRE <key> <time-in-sec>
4. ZADD <key> <score1> <member1> <score2> <member2> ...
5. ZRANK <key> <member>
6. ZRANGE <key> <start> <end>
7. QUIT

