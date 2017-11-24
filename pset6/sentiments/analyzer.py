import nltk
import sys
import os



class Analyzer():
    """Implements sentiment analysis."""

    def conf(self, doc):
        """Een conf funcite om de input aan te passen."""
        if doc != ';':
            return doc



    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        # open strip eventuele extra's en conf eventuele ongewenste text
        self.post_fset = set(line.strip() for line in self.conf(
            open(positives,'r')))
        self.neg_fset = set(line.strip() for line in self.conf(
            open(negatives,'r')))


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        # Deze variabele maken als retrun value.
        sentiment = 0
        # Maak een set van de text
        text = set([text.lower()])

        # Vergelijk de set() en return de juiste hoeveelheid
        if len(text & self.post_fset) > 0:
            sentiment += 1
        elif len(text & self.neg_fset) > 0:
            sentiment -= 1
        return sentiment


