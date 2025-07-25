export type NavItem = {
  title: string;
  href: string;
  disabled?: boolean;
};

export type MainNavItem = NavItem;

export type SidebarNavItem = {
  title: string;
  disabled?: boolean;
  external?: boolean;
  icon?: any;
  href?: string;
};

export type PublicUser = {
  id: string;
  name: string;
  online: boolean;
  inGame: boolean;
  pfp: string;
};

export type User = {
  id: number;
  id42: number;
  email: string;
  username: string;
  pfp: string;
  status: boolean;
  tfaEnabled: boolean;
  tfaVerified: boolean;
  tfaOTP: string | null;
  inGame: boolean;
  createdAt: string;
  updatedAt: string;
};

export type DashboardConfig = SidebarNavItem[];
