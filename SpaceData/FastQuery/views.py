from django.shortcuts import render, redirect
from django.http.response import HttpResponse
from . import forms
from django.views.static import serve
from django.views import View
from . import utils
import os
import time

from FastQuery import generic, query1, query2, query3
from SpaceData.wsgi import star_info, cube_info, neighbour_info
from FastQuery.datatype import Star, Cube, StarInfo

def keyfunction(star):
    return star.distance

class DashboardView(View):
    template_name = 'FastQuery/home.html'

    def get(self, request):
        return render(request, self.template_name)

class DatasetView(View):
    template_name = 'FastQuery/dataset.html'

    def get(self, request):
        files = utils.list_files()
        return render(request, self.template_name, {'files': files})

class DownloadView(View):
    template_name = 'FastQuery/dataset.html'

    def get(self, request):
        filename = request.GET.get('file')
        if filename:
            if filename == 'compressed.zip':
                file = utils.get_file(filename)
                response = HttpResponse(file, content_type = 'compressed/zip')
                response['Content-Disposition'] = 'attachment; filename=' + filename
                return response
            else:
                file = utils.get_file(filename)
                response = HttpResponse(file, content_type = 'text/plain')
                response['Content-Disposition'] = 'attachment; filename=' + filename
                return response

class QueryView(View):
    template_name = 'FastQuery/query.html'

    def get(self, request):
        return render(request, self.template_name)

class Query1View(View):
    template_name = 'FastQuery/query1.html'

    def get(self, request):
        form = forms.Query1Form()
        return render(request, self.template_name, {'form': form})

    def post(self, request):
        form = forms.Query1Form(request.POST)
        if form.is_valid():
            x = float(form.cleaned_data.get('x'))
            y = float(form.cleaned_data.get('y'))
            z = float(form.cleaned_data.get('z'))
            cube = generic.get_cube_id(x, y, z)
            if cube == Cube(-1, -1, -1, -1):
                return render(request, self.template_name, {'form': form, 'err': 1, 'msg': 'Cube dimension not supported'})

            if 'list' not in request.POST:
                start_time = time.time()
                ans1, ans2 = query1.count(cube)
                end_time = time.time()
                return render(request, self.template_name, {'form': form, 'ans1': ans1, 'ans2': ans2, 'total': ans1 + ans2, 'time': end_time - start_time})

            elif 'list' in request.POST:
                start_time = time.time()
                ans1, ans2, L = query1.list_stars(cube, x, y, z)
                end_time = time.time()
                return render(request, self.template_name, {'form': form, 'ans1': ans1, 'ans2': ans2, 'total': ans1 + ans2, 'list': L, 'time': end_time - start_time})
        else:
            return render(request, self.template_name, {'form': form, 'err': 1, 'msg': 'Invalid Submission'})

class Query2View(View):
    template_name = 'FastQuery/query2.html'

    def get(self, request):
        form = forms.Query2Form()
        return render(request, self.template_name, {'form': form})

    def post(self, request):
        form = forms.Query2Form(request.POST)
        if form.is_valid():
            x = float(form.cleaned_data.get('x'))
            y = float(form.cleaned_data.get('y'))
            z = float(form.cleaned_data.get('z'))
            cube = generic.get_cube_id(x, y, z)
            if cube == Cube(-1, -1, -1, -1):
                return render(request, self.template_name, {'form': form, 'err': 1, 'msg': 'Cube dimension not supported'})

            start_time = time.time()
            stars = query2.BFS(cube, x, y, z, float(form.cleaned_data.get('radius')))
            end_time = time.time()

            # D = {}
            # S = []
            #
            # for star in stars:
            #     if star not in D:
            #         D[star] = 1
            #         S.append(star)
            #
            # S = sorted(S, key=keyfunction)

            if 'list' not in request.POST:
                return render(request, self.template_name, {'form': form, 'stars': len(stars), 'time': end_time - start_time})

            elif 'list' in request.POST:
                return render(request, self.template_name, {'form': form, 'stars': len(stars), 'list': stars, 'time': end_time - start_time})
        else:
            return render(request, self.template_name, {'form': form, 'err': 1, 'msg': 'Invalid Submission'})

class Query3View(View):
    template_name = 'FastQuery/query3.html'

    def get(self, request):
        form = forms.Query3Form()
        return render(request, self.template_name, {'form': form})

    def post(self, request):
        form = forms.Query3Form(request.POST)
        if form.is_valid():
            x = float(form.cleaned_data.get('x'))
            y = float(form.cleaned_data.get('y'))
            z = float(form.cleaned_data.get('z'))
            cube = generic.get_cube_id(x, y, z)
            if cube == Cube(-1, -1, -1, -1):
                return render(request, self.template_name, {'form': form, 'err': 1, 'msg': 'Cube dimension not supported'})

            start_time = time.time()
            stars = query3.find_spiral_arm(cube, x, y, z)
            end_time = time.time()

            return render(request, self.template_name, {'form': form, 'stars': len(stars), 'list': stars, 'time': end_time - start_time})
        
        else:
            return render(request, self.template_name, {'form': form, 'err': 1, 'msg': 'Invalid Submission'})

class NaiveView(View):
    template_name = 'FastQuery/naive.html'

    def get(self, request):
        form = forms.Query2Form()
        return render(request, self.template_name, {'form': form})

    def post(self, request):
        form = forms.Query2Form(request.POST)
        if form.is_valid():
            x = float(form.cleaned_data.get('x'))
            y = float(form.cleaned_data.get('y'))
            z = float(form.cleaned_data.get('z'))
            cube = generic.get_cube_id(x, y, z)
            if cube == Cube(-1, -1, -1, -1):
                return render(request, self.template_name, {'form': form, 'err': 1, 'msg': 'Cube dimension not supported'})

            start_time = time.time()
            stars = query2.naive(cube, x, y, z, float(form.cleaned_data.get('radius')))
            end_time = time.time()

            if 'list' not in request.POST:
                return render(request, self.template_name, {'form': form, 'stars': len(stars), 'time': end_time - start_time})

            elif 'list' in request.POST:
                return render(request, self.template_name, {'form': form, 'stars': len(stars), 'list': stars, 'time': end_time - start_time})
        else:
            return render(request, self.template_name, {'form': form, 'err': 1, 'msg': 'Invalid Submission'})
