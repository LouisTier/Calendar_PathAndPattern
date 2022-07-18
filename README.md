# Calendar : Shortest path and pattern identification

## **1. About this project**

This project is divided into **two parts**. For a given schedule, you will need to:
  - **Find the shortest path** for a particular year between two days
  - **Identify the pattern** of a given calendar (see the 10 examples in the _Data_ folder) over several years

Of course, many elements are to be taken into account to carry out this project in particular **characterize the starting day of a year** or **check if a year is leap year or not**.

## **2. Find the shortest path by connecting two dates in the annual calendars**

Here is a first idea of how to approach the problem:

<div id="first idea" align = "center">
  <img src="https://user-images.githubusercontent.com/105392989/174974823-149e08a8-df25-4a30-947f-7609ad357e73.png" width="750">
</div>

Obviously to have this notion of distance, the months must **fit together and not be cut up** as before. So we need to have the following version: 

<div id="second picture" align = "center">
  <img src="https://user-images.githubusercontent.com/105392989/174974880-a65249e2-9365-4248-a35d-ac91aa470980.png" width="750">
</div>

_Attention: On the previous image we consider that there are 3 sections. In reality, **only one section should be considered**, otherwise the notion of distance does not make sense!_

I define the **notion of distance** as follows:  
**For two dates chosen in January of a defined year, J<sup>month</sup><sub>1</sub>(x,y), J<sup>month</sup><sub>2</sub>(x,y) with x is the day of the week (from 0 to 6), y is the week number of the year.**   
We reason with a **Cartesian plane** and the **Euclidean distance**.

Here are **some constraints** for this first part:
  - From year 1900 to 2022
  - ``` (J<sup>month</sup><sub>1</sub> - J<sup>month</sup><sub>2</sub>) modulo 7 != 0 ```
  - ``` max(J<sup>month</sup><sub>1</sub>, J<sup>month</sup><sub>2</sub>) <= 27 ```

To carry out this first part of the project, I split the problem into 3 categories: 
  - Generate a yearly calendar and save it in text format
  - For two defined variables _(J<sup>month</sup><sub>1</sub>(x,y), J<sup>month</sup><sub>2</sub>(x,y))_, identify the shortest path 
  - For a given year, return the pair of variables _(J<sup>month</sup><sub>1</sub>(x,y), J<sup>month</sup><sub>2</sub>(x,y))_ that constitutes the shortest path

## **3. Identify the pattern (monthly calendar)**

In this second part, we try to **find the set of years where a defined pattern is located**. Here is an example of a pattern to find: 

<div id="pattern" align = "center">
  <img src="https://user-images.githubusercontent.com/105392989/174982463-8ee12774-b0ca-4a1b-b15c-7a986a645a3b.png" width="550">
</div>

For this part, I take into consideration the following **constraints**: 
  - From year 1900 to 2022
  - Reading of calendar files with potentially slightly different formats _(especially the separators)_

And to solve this, we must:
- Transform a file in text format into a matrix
- List the years (and months) that have the same monthly calendar
