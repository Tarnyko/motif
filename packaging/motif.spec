%bcond_with x

Name:           motif
Version:        2.3.4
Release:        0
Summary:        GUI toolkit for UNIX, X11-based
License:        LGPL-2.1
Group:          Graphics & UI Framework/API
Url:            http://sourceforge.net/projects/motif

Source0:        %name-%version.tar.xz
Source1:        %name.manifest
BuildRequires:	autoconf >= 2.64, automake >= 1.11
BuildRequires:  libtool >= 2.2
BuildRequires:  byacc
BuildRequires:  flex
BuildRequires:  libjpeg6-devel
BuildRequires:  libpng-devel
BuildRequires:  pkgconfig
BuildRequires:  pkgconfig(ice)
BuildRequires:  pkgconfig(x11)
BuildRequires:  pkgconfig(xbitmaps)
BuildRequires:  pkgconfig(xft)
BuildRequires:  pkgconfig(xmu)
BuildRequires:  pkgconfig(xrender)
BuildRequires:  pkgconfig(xt)

%if !%{with x}
ExclusiveArch:
%endif

%description
OSF/Motif is the industry standard UNIX GUI toolkit, based upon X11. It relies on Xt to provide an extended widget set.

%package devel
Summary:	Development components for the %{name} package
Group:		Development/Libraries
Requires:	%{name} = %{version}

%description devel
Development files for %{name}.

%package tools
Summary:        Tools for the %{name} package
Group:          Graphics & UI Framework/Utilities
Requires:       %{name} = %{version}

%description tools
Development files for %{name}, including MWM (Motif Window Manager).


%prep
%setup -q
cp %{SOURCE1} .

%build
%autogen
make %{?_smp_mflags}

%install
%make_install
rm -rf %{buildroot}%{_datadir}

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%defattr(-,root,root)
%license COPYING
%{_libdir}/*.so.*

%files devel
%manifest %{name}.manifest
%defattr(-,root,root)
%{_includedir}/*
%{_libdir}/*.so

%files tools
%manifest %{name}.manifest
%defattr(-,root,root)
%{_bindir}/*
%{_libdir}/X11/*

%changelog
