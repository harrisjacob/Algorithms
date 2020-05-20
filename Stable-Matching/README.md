# Stable Matching

## Description
The stable matching problem involves finding a stable match between two equal sized pools of elements.  Elements of each pool rank all elements of the other pool by their match preference.  A match is considered unstable if an element (E) of that match has a higher preference in a different element over its current match, and that different element has a higher preference in E than in its own match.  Similarly, if two non-matched elements of opposite pools prefer each other over their current matches, the matches are consider to be unstable.

For a formal description of the problem [see here](https://en.wikipedia.org/wiki/Stable_marriage_problem "Stable Marriage Problem").

## Purpose
The purpose of this project was to examine and implement various applicable algorithms, practice templated classes, templated functions, and basic OOP.

## Contextual Implementation
In the context of this implementation, the two pools are of teachers and students.  Teachers can only have one student and students can only have one teacher.  For some strange reason, teacher salary is dependent on student performance, thus it is in the teacher's best interest to choose the student they percieve to be the highest performing (get the highest grade).  Similarly, students believe that their grade depends on the teacher they register with.  Thus, it is in the student's best interest to choose the teacher that they percieve to be the best at their job.  Because every student would rather match with a teacher than not match at all for fear of not recieving a grade, each student decides to rank every teacher in order of preference.  Similarly, no teacher wants to be without a student (thus no paycheck) and decides to rank every student in order of preference.

## Algorithms
The Gale-Shapley algorithm can be found [here](https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm "Gale-Shapley algorithm").

## Application
Realistically, stable matching is used in a wide variety of contexts.  Noteably, the National Resident Matching Program ([NRMP](https://en.wikipedia.org/wiki/National_Resident_Matching_Program#Matching_algorithm "National Resident Matching Program")) uses a version of the stable matching problem to provide placement for medical school students into medical residency training programs on [Match Day](https://en.wikipedia.org/wiki/Match_Day_(medicine) "Match Day").

## Datafile Restrictions
* Both datafiles must have 10 entries
* Each entry must consist of a name, an ID, and 10 space delimited IDs of the opposite pool ordered by preference (highest to loweset)
* Each entry must be newline terminated
* Each entry must list the IDs of entries in the opposite datafile exactly once
* Each entry must have the space delimited format: [name] [id] [prefernces]
* Student IDs must be in the range 0-9
* Teacher IDs must be in the range 10-19
* Every student and teacher must have a unique ID.

*Example entry: Charles 0 10 11 12 13 14 15 16 17 18 19*

*Charles is a student because his ID (0) is in the range 0-9.*
