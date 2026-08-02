---
title: Databases
---

# Databases

**Artifact:** Customer, order, and RMA database
**Original course:** DAD 220

## Description

This artifact is a set of SQL queries and documentation from my DAD 220 database course. It covers importing customer, order, and RMA data into MySQL tables, then writing queries to count and filter records by location, insert and update records, delete records, and export query results to a CSV file. I created this before starting CS 499.

## Justification and Enhancement

I picked this artifact because working with it critically surfaced real issues I could fix, not just theoretical ones I had to invent. The original UPDATE statement had a genuine syntax error, a missing closing quote, that would have failed if run as written. Some queries used `UPPER()` for case-insensitive comparisons and others did not, which was inconsistent. None of the tables had any indexing beyond the default primary key, even though most queries filtered or joined on city, state, or customer ID. And the delete statement had no transaction protection around it. I fixed the syntax error, standardized the case-insensitive comparisons across all the queries, added indexes on the columns that are filtered and joined most often, used `EXPLAIN` to compare the query plan before and after indexing, and wrapped the destructive delete in a transaction so it can be checked before being made permanent.

## Course Outcomes

This met outcome three, since the indexing and `EXPLAIN` comparison let me directly show the impact of a real design decision rather than just asserting that indexing helps. No real updates to my outcome coverage plan, this still targets the same outcome I identified in Module One, though the scope ended up a bit broader than originally planned since I also fixed the syntax bug and the inconsistent case handling along the way.

## Reflection

Going back through my own SQL for this made me realize how easy it is to write a query that looks right and never actually verify it runs. The UPDATE statement is the clearest example, it read fine on a glance but had a real syntax error I had missed entirely until I reviewed it against the checklist. The main challenge was scoping the enhancement so it felt substantial without turning it into an entirely different project, since indexing alone would have been a fairly thin improvement on its own, which is part of why I bundled it with the other three fixes.
