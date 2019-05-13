from django import forms

class Query1Form(forms.Form):
    x = forms.FloatField(required = True)
    y = forms.FloatField(required = True)
    z = forms.FloatField(required = True)

class Query2Form(forms.Form):
    x = forms.FloatField(required = True)
    y = forms.FloatField(required = True)
    z = forms.FloatField(required = True)
    radius = forms.FloatField(required = True)
