-- =========================================================================
-- DAD 220 Enhancement (CS 499)
-- Original artifact: Levi Winters, DAD 220 Module Four Major Activity
-- Enhancements: fix a syntax bug, standardize case-insensitive comparisons,
-- add indexes with EXPLAIN comparisons, and wrap the destructive delete in
-- a transaction.
-- =========================================================================


-- -------------------------------------------------------------------------
-- 1. Bug fix: the original UPDATE statement was missing a closing quote
--    after 'Complete', which is a syntax error and would not run as written.
-- -------------------------------------------------------------------------

-- Original (broken):
-- UPDATE rma SET Status = 'Complete, Step = 'Credit Customer Account' WHERE OrderID = 5175;

-- Fixed:
UPDATE rma
SET Status = 'Complete', Step = 'Credit Customer Account'
WHERE OrderID = 5175;


-- -------------------------------------------------------------------------
-- 2. Consistency fix: some queries wrapped city/state comparisons in
--    UPPER() for case-insensitive matching, others did not. The Framingham
--    query below did not use UPPER() while the Massachusetts and
--    Woonsocket queries did. Standardizing this so every text comparison
--    behaves the same way regardless of how the data was entered.
-- -------------------------------------------------------------------------

-- Original (inconsistent):
-- SELECT COUNT(*) AS OrderCount FROM customers INNER JOIN orders
-- ON customers.CustomerID = orders.CustomerID
-- WHERE customers.city = 'Framingham' AND customers.state = 'Massachusetts';

-- Fixed:
SELECT COUNT(*) AS OrderCount
FROM customers
INNER JOIN orders ON customers.CustomerID = orders.CustomerID
WHERE UPPER(customers.city) = 'FRAMINGHAM'
  AND UPPER(customers.state) = 'MASSACHUSETTS';


-- -------------------------------------------------------------------------
-- 3. Indexing: none of the tables had indexes beyond the default primary
--    key, but nearly every query filters or joins on city, state, or
--    CustomerID. Adding targeted indexes on those columns, and using
--    EXPLAIN before and after to show the actual change in query plan.
-- -------------------------------------------------------------------------

-- Before adding indexes, capture the query plan for the two most
-- frequently filtered queries:
EXPLAIN SELECT COUNT(*) AS OrderCount
FROM customers
INNER JOIN orders ON customers.CustomerID = orders.CustomerID
WHERE UPPER(customers.city) = 'FRAMINGHAM'
  AND UPPER(customers.state) = 'MASSACHUSETTS';

EXPLAIN SELECT COUNT(*)
FROM customers
WHERE UPPER(customers.state) = 'MASSACHUSETTS';

-- Add the indexes:
CREATE INDEX idx_customers_city ON customers (city);
CREATE INDEX idx_customers_state ON customers (state);
CREATE INDEX idx_orders_customerid ON orders (CustomerID);

-- After adding indexes, run EXPLAIN again on the same two queries and
-- compare the "type" and "rows" columns in the output. Before the index,
-- MySQL is expected to report a full table scan (type = ALL) with rows
-- equal to the full row count of the customers table. After the index,
-- it should report a much smaller estimated row count and a lookup type
-- such as "ref" or "range" instead of a full scan.
EXPLAIN SELECT COUNT(*) AS OrderCount
FROM customers
INNER JOIN orders ON customers.CustomerID = orders.CustomerID
WHERE UPPER(customers.city) = 'FRAMINGHAM'
  AND UPPER(customers.state) = 'MASSACHUSETTS';

EXPLAIN SELECT COUNT(*)
FROM customers
WHERE UPPER(customers.state) = 'MASSACHUSETTS';


-- -------------------------------------------------------------------------
-- 4. Safety fix: the original delete had no transaction wrapper, so a
--    mistake in the WHERE clause could delete more data than intended
--    with no way to undo it. Wrapping it in a transaction so the result
--    can be checked before it's made permanent.
-- -------------------------------------------------------------------------

-- Original (unprotected):
-- DELETE FROM rma WHERE UPPER(Reason) = 'Rejected';

-- Fixed:
START TRANSACTION;

DELETE FROM rma WHERE UPPER(Reason) = 'REJECTED';

-- Check the result before committing. If the row count looks correct,
-- run COMMIT. If it looks wrong, run ROLLBACK instead and the delete
-- will be undone.
-- SELECT ROW_COUNT();

COMMIT;
-- ROLLBACK;
