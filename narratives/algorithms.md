---
title: Algorithms and Data Structures
---

# Algorithms and Data Structures

**Artifact:** Course advisor program (pseudocode)
**Original course:** CS 300

## Description

This artifact is pseudocode I wrote for CS 300, a data structures and algorithms course, designing a course advisor program that loads courses from a file and lets a user print them alphabetically or look up a specific course and its prerequisites. I wrote versions using a vector, a hashtable, and a tree, compared their runtime complexity, and picked a hashtable as the best fit. I created this before starting CS 499.

## Justification and Enhancement

I picked this artifact because it already involved real algorithmic decision making, comparing three data structures by Big O complexity before choosing one, which fits directly with the algorithms and data structures outcome. The hashtable version only found a course's direct prerequisites and had a loop that could run forever if two courses ever referenced each other as prerequisites. I improved it by adding a recursive, depth first function that walks the full prerequisite chain instead of just one level, along with a visited set that detects and reports any circular relationship instead of looping infinitely.

## Course Outcomes

This met outcome three, since the enhancement is a clear algorithmic improvement I can explain, moving from a shallow one level lookup to a full recursive traversal with cycle detection. No updates to my outcome coverage plan, this artifact still targets the same outcome I identified in Module One.

## Reflection

Working on this taught me to look closely at loop logic instead of assuming it does what its name suggests. The original function was named like it counted all prerequisites, but it only ever expanded one level deeper before stopping. The main challenge was keeping the pseudocode consistent with the style and structure of my original work, so the enhancement reads as a natural extension rather than a completely different approach.
