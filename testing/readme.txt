Test cases are sorted by folders into test suites depending of their purpose.

Test file format:
*beginning*
*DESCRIPTION SECTION*
description section $number of description lines$
preConditions: <...>
Test description: <...>
PostConditions: <...>
*TEST DATA SECTION*
*input data*
*expected output*
*end of file*

Types of the tests:
	Posinitve -- test with correct input
	Negative -- test with uncorrect input

Types of the test results:
	Positive -- test is passed
	Negative -- test is failed
	Blocked -- testing is impossible, failed

Each test should have: 
	PreConditions -- conditions that must be fulfilled before the testing 
	Test case description -- list of actions to obtain a result
	<PostConditions> -- list of actions to return system to its initial state