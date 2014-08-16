import os
import platform
env = Environment(ENV = os.environ, tools=['default'], toolpath='.')

# enable choosing other compilers
env["CC"] = os.getenv("CC") or env["CC"]
env["CXX"] = os.getenv("CXX") or env["CXX"]
env["ENV"].update(x for x in os.environ.items() if x[0].startswith("CCC_"))

env.Append(CPPPATH = ['#src'])
env.Append(LIBPATH = ['#src'])
env.Append(CFLAGS = ['-g'])
env.Append(CPPFLAGS = ['-g'])

Export("env")

# Main Program
SConscript('#src/SConscript')
