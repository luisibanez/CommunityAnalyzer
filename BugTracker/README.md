Example usage
-------------
Make sure you have MongoDB started.
```
mongod &
```

Load the firefox bugs into MongoDB
```
python bugzillaProjectBugs.py https://bugzilla.mozilla.org firefox localhost community firefox.bugs
```

Fix the date fields to be true datetime objects
```
python bugzillaParseDates.py localhost community firefox.bugs firefox.bugs.datefix
```

Extract history data one bug at a time
```
python bugzillaHistory.py https://bugzilla.mozilla.org localhost community firefox.bugs.datefix firefox.bugs.history
```
