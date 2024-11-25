from django.http import JsonResponse

def get_data(request):
    name = request.GET.get('name', 'Guest')
    response = {"message": f"Hello, {name}!"}
    return JsonResponse(response)
